/* list.h
 *
 * This is a minimalistic and very specific list implementaion with no
 * ownership semantics.
*/

typedef struct LIST LIST;

LIST *list_create();
void list_destroy(LIST *doomed);
void list_put(LIST *, const char *key, unsigned char *data);
unsigned char *list_get(LIST *, const char *key);
void list_start_it(LIST *list, const char **key, unsigned char **data);
void list_next_it(LIST *list, const char **key, unsigned char **data);
