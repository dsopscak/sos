/* quick_crypt.c
 */

#include "quick_crypt.h"

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include "sha256.h"
#include "list.h"

struct QC
    {
    FILE *f;
    unsigned char *data;
    LIST *list;
    };

QC *quick_crypt_create(const char *filename)
    {
    QC *ctx = NULL;
    FILE *f = fopen(filename, "a+");
    if (f)
        {
        ctx = malloc(sizeof(QC));
        ctx->list = list_create();
        ctx->f = f;
        fseek(f, 0L, SEEK_END);
        long file_size = ftell(f);
        if (file_size)
            {
            ctx->data = malloc(file_size);
            rewind(ctx->f);
            fread(ctx->data, 1, file_size, f);

            char *key = ctx->data;
            char *p = ctx->data;

            while (1)
                {
                while (*p) ++p;
                if (! *++p) break;
                list_put(ctx->list, key, p);
                p += SHA256_BLOCK_SIZE;
                key = p;
                }
            }
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

