/* quick_crypt.c
 */

#include "quick_crypt.h"

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "sha256.h"
#include "list.h"

struct QC
    {
    FILE *f;
    unsigned char *data;
    LIST *list;
    unsigned char temp_hash[SHA256_BLOCK_SIZE];
    unsigned char temp_data[SHA256_BLOCK_SIZE];
    };

QC *quick_crypt_create(const char *filename)
    {
    QC *ctx = NULL;
    FILE *f = fopen(filename, "rb+"); // Need the b for windows
    if (f)
        {
        ctx = malloc(sizeof(QC));
        ctx->list = list_create();
        ctx->f = f;
        ctx->data = NULL;
        fseek(f, 0L, SEEK_END);
        long file_size = ftell(f);
        if (file_size)
            {
            ctx->data = malloc(file_size);
            rewind(ctx->f);
            fread(ctx->data, 1, file_size, f);

            const char *key = (const char *)ctx->data;
            unsigned char *p = ctx->data;

            while (1)
                {
                while (*p) ++p;
                if (! *++p) break;
                list_put(ctx->list, key, p);
                p += SHA256_BLOCK_SIZE;
                key = (const char *)p;
                }
            }
        }
    else if (errno == ENOENT)
        {
        f = fopen(filename, "wb");
        if (f)
            {
            ctx = malloc(sizeof(QC));
            ctx->list = list_create();
            ctx->f = f;
            ctx->data = NULL;
            }
        else
            perror(NULL);
        }
    else
        perror(NULL);

    return ctx;
    }

void quick_crypt_destroy(QC *doomed)
    {
    free(doomed->data);
    free(doomed);
    }

int quick_crypt_save(QC *qc)
    {
    rewind(qc->f);
    const char *key;
    unsigned char *data;
    for (list_start_it(qc->list, &key, &data);
        key && data;
        list_next_it(qc->list, &key, &data))
        {
        fputs(key, qc->f);
        fputc(0, qc->f);
        fwrite(data, SHA256_BLOCK_SIZE, 1, qc->f);
        }
    fputc(0, qc->f); // consecutive null chars => EOD
    fputc(0, qc->f);
    return 0;
    }

static void hash(QC *qc, const char *pass, const char *salt)
    {
    SHA256_CTX ctx;
    sha256_init(&ctx);
    sha256_update(&ctx, (unsigned char *)pass, strlen(pass));
    sha256_update(&ctx, (unsigned char *)salt, strlen(salt));
    sha256_final(&ctx, qc->temp_hash);
    }

static void xor_data(unsigned char *a, unsigned char *b, unsigned char *tgt)
    {
    for (int i =0; i < SHA256_BLOCK_SIZE; ++i)
        tgt[i] = (a[i] ^ b[i]);
    }

const char *quick_crypt_get(QC *qc, const char *key, const char *passphrase)
    {
    unsigned char *data = list_get(qc->list, key);
    if (data)
        {
        hash(qc, passphrase, key);
        xor_data(data, qc->temp_hash, qc->temp_data);
        return (const char *)qc->temp_data;
        }
    // else
    return NULL;
    }

int quick_crypt_put(QC *qc, 
                    const char *key, 
                    const char *passphrase, 
                    const char *s)
    {
    if (strlen(s) > SHA256_BLOCK_SIZE - 1)
        return -1;
    char tbuf[SHA256_BLOCK_SIZE];
    strncpy(tbuf, s, sizeof(tbuf));
    hash(qc, passphrase, key);
    xor_data(qc->temp_hash, (unsigned char *)tbuf, qc->temp_data);

    /* NOTE: the following is *bad* if done more than once in lifetime
     * of qc 
     */
    list_put(qc->list, key, qc->temp_data);
    return 0;
    }

