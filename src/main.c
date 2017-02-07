/* main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "quick_crypt.h"

void usage()
    {
    printf("usage: qc <file> <passphrase> <key> [<value>]\n");
    exit(-1);
    }

int main(int argc, char *argv[])
    {
    if (argc < 4 || argc > 5)
        usage();

    QC *qc = quick_crypt_create(argv[1]);
    if (qc)
        {
        ;
        }
    else
        {
        printf("qc: init error with file [%s]\n", argv[1]);
        exit(-1);
        }
    }
    
