/* list_test.c
 */
#include "list.h"

#include <stdio.h>

char data[] =
{ 
'A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A',
'B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B',
'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',
'D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D',
'E','E','E','E','E','E','E','E','E','E','E','E','E','E','E','E','E','E','E','E','E','E','E','E','E','E','E','E','E','E','E','E',
'Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z'
};

char *key_data[] = {"aaa", "b", "cccc", "dd", "eeeeeeeeeeeeeeeeeeeeeeeee"};

static void print_list(LIST *list)
    {
    const char *k;
    unsigned char *d;

    for (list_start_it(list, &k, &d); k; list_next_it(list, &k, &d))
        {
        printf("[%s]=>[", k);
        fwrite(d, 32, 1, stdout);
        printf("]\n");
        }
    }

int main()
    {
    LIST *list = list_create();
    for (int i = 0; i < 5; ++i)
        list_put(list, key_data[i], data + i * 32);

    print_list(list);
    list_put(list, "cccc", data + 5 * 32);
    print_list(list);

    list_destroy(list);

    return 0;
    }

