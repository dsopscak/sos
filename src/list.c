/* list.c
 */
#include "list.h"
#include <stdlib.h>
#include <string.h>

typedef struct NODE
    {
    const char *key;    
    unsigned char *data;
    struct NODE *next;
    } NODE;

struct LIST
    {
    NODE *first;
    NODE *last;
    NODE *it;
    };

LIST *list_create()
    {
    LIST *list = malloc(sizeof(LIST));
    list->first = NULL;
    list->last = NULL;
    list->it = NULL;

    return list;
    }

static NODE *find(LIST *list, const char *key)
    {
    NODE *node = list->first; 
    for ( ; node && strcmp(key, node->key); node = node->next)
        ; /* no-op */
    return node;
    }

void list_destroy(LIST *doomed)
    {
    NODE *node = doomed->first; 
    while (node)
        {
        NODE *shorty = node;
        node = node->next;
        free(shorty);
        }
    free(doomed);    
    }

void list_put(LIST *list, const char *key, unsigned char *data)
    {
    NODE *spot = find(list, key);
    if (spot)
        {
        spot->data = data;
        }
    else
        {
        NODE *node = malloc(sizeof(NODE));
        node->key = key;
        node->data = data;
        node->next = NULL;
        if (list->last)
            {
            list->last->next = node;
            list->last = node;
            }
        else
            list->first = list->last = node;
        }
    }

unsigned char *list_get(LIST *list, const char *key)
    {
    NODE *node = find(list, key);
    if (node)
        return node->data;
    return NULL;
    }

void list_start_it(LIST *list, const char **key, unsigned char **data)
    {
    list->it = list->first;
    if (list->it)
        {
        *key = list->it->key;
        *data = list->it->data;
        }
    else
        {
        *key = NULL;
        *data = NULL;
        }
    }

void list_next_it(LIST *list, const char **key, unsigned char **data)
    {
    list->it = list->it->next;
    if (list->it)
        {
        *key = list->it->key;
        *data = list->it->data;
        }
    else
        {
        *key = NULL;
        *data = NULL;
        }
    }
