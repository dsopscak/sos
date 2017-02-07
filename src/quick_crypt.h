/* quick_crypt.h
 */

typedef struct QC QC;

QC *quick_crypt_create(const char *filename);
void quick_crypt_destroy(QC *doomed);

/* Add or update */
int quick_crypt_put(QC *,
  const char *key, const char *passphrase, const char *value);

/* Get existing 0-terminated string value */
const char *quick_crypt_get(QC *, const char *key, const char *passphrase);

/* Write current state of context */
int quick_crypt_save(QC *);
