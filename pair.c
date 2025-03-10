/* pair.c: Key/Value Pair Structure */

#include "pair.h"

#include <stdlib.h>
#include <string.h>

/**
 * Allocate and initialize new Pair structure.
 *
 * @param   key             Pair's key.
 * @param   value           Pair's value.
 * @return  New Pair structure (must be deleted later).
 **/
Pair *pair_create(const char *key, long value) {
    Pair *p = calloc(1, sizeof(Pair));
    p->key = strdup(key);
    p->value = value;
    return p;
}

/**
 * Delete Pair structure.
 *
 * @param   p               Pointer to Pair structure.
 **/
void pair_delete(Pair *p) {
    free(p->key);
    free(p);
}

/**
 * Format Pair by writing to stream.
 *
 * @param   p               Pointer to Pair structure.
 * @param   stream          File stream to write to.
 **/
void pair_print(Pair *p, FILE *stream) {
    fprintf(stream, "%ld\t%s\n" , p->value, p->key);
}
