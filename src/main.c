/* main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "quick_crypt.h"

void usage()
    {
    printf("usage: sos <file> <passphrase> <key> [<value>]\n");
    exit(-1);
    }

int main(int argc, char *argv[])
    {
    if (argc < 4 || argc > 5)
        usage();

    QC *qc = quick_crypt_create(argv[1]);
    if (qc)
        {
        if (argc == 4)
            {
            const char *s = quick_crypt_get(qc, argv[3], argv[2]);
            if (s)
                printf("%s\n", s);
            else
                return 1;
            }
        else
            {
            quick_crypt_put(qc, argv[3], argv[2], argv[4]);
            quick_crypt_save(qc);
            }

        }
    else
        {
        printf("qc: init error with file [%s]\n", argv[1]);
        exit(-1);
        }

    return 0;
    }
    
