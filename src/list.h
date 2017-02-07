/* list.h
*/

typedef struct LIST LIST;

LIST *list_create();
void list_destroy(LIST *doomed);
void list_put(LIST *, const char *key, unsigned char *data);
unsigned char *list_get(LIST *, const char *key);
