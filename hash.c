#include "hash.h"
#include <string.h>

/**
 * Constants
 * http://isthe.com/chongo/tech/comp/fnv/
 **/

#define FNV_OFFSET_BASIS    (0xcbf29ce484222325ULL)
#define FNV_PRIME           (0x100000001b3ULL)

/**
 * Compute FNV-1a hash.
 * @param   data    Data to hash.
 * @param   n       Number of bytes in data.
 * @return          Computed FNV-1a hash as 64-bit unsigned integer.
 **/
long fnv_hash(const char *data) {
    long hash = FNV_OFFSET_BASIS;
    const char *c = data;
    int n = strlen(data);

    for (int i = 0; i < n; i++) {
        hash = hash ^ c[i];
        hash = hash * FNV_PRIME;
    }

    return hash;
}

