/* main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quick_crypt.h"

void usage()
    {
    printf("usage: sos passphrase file key [value]\n");
    exit(-1);
    }

int main(int argc, char *argv[])
    {
    if (argc < 4 || argc > 5)
        usage();

    char *pass = argv[1];
    if (pass[0] == '-')
        {
        pass = calloc(1,1);
        char buffer[128];
        while (fgets(buffer, sizeof(buffer), stdin))
            {
            pass = realloc(pass, strlen(pass) + 1 + strlen(buffer));
            strcat(pass, buffer);
            }
        }

    const char *file_name = argv[2];
    const char *key = argv[3];

    QC *qc = quick_crypt_create(file_name);
    if (qc)
        {
        if (argc == 4)
            {
            const char *s = quick_crypt_get(qc, key, pass);
            if (s)
                printf("%s\n", s);
            else
                {
                fprintf(stderr, "[%s] not found in %s\n", key, file_name);
                exit(-1);
                }
            }
        else
            {
            const char *value = argv[4];
            if (quick_crypt_put(qc, key, pass, value))
                {
                fprintf(stderr, "sos failed\n");
                exit(-1);
                }

            quick_crypt_save(qc);
            }

        }
    else
        {
        fprintf(stderr, "qc: init error with file [%s]\n", file_name);
        exit(-1);
        }

    return 0;
    }
    
