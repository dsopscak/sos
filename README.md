# sos
### shack of secrets

A simple tool focused on quick encryption and decryption of short (< 32) strings. 

Has two modes:

`$ sos <passphrase> <file> <key>`

which prints to stdout the decrypted string from the given file associated with the given key, and

`$ sos <passphrase> <file> <key> <new string>`

which inserts/updates the string associated with the given key. If passphrase is -, reads that from standard input.

Uses simple (hopefully strong enough) encryption based on the SHA256 hash of the passphrase. XOR's the plaintext/cyphertext with the hashed passphrase salted with the key. The 32 byte limit insures that bytes in the hash are used not more than once.

