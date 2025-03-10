#include "table.h"
#include <string.h>

/**
 * Allocate and initialize new Table structure.
 *
 * @param   capacity        Number of buckets in the hash table.
 * @param   alpha           Maximum load factor for hash table.
 * @param   hash            Hash function to use for hash table.
 * @return  New Table structure (must be deleted later).
 **/

Table *table_create(int capacity, double alpha) {
    if (capacity <= 0) {
        capacity = DEFAULT_CAPACITY;
    }
    Table *t = calloc(1, sizeof(Table));  // Allocate memory for the Table struct
    t->buckets = calloc(capacity, sizeof(Pair *));  // Allocate and initialize buckets array
    t->capacity = capacity;
    t->size = 0;
    t->alpha = alpha;
    return t;
}

/**
 * Release internal pairs and buckets and then the Table structure itself.
 *
 * @param   t               Pointer to the Table structure.
 **/
void table_delete(Table *t) {
    if (!t) return;
    for (int i = 0; i < t->capacity; i++) {
        if (t->buckets[i]) {
            pair_delete(t->buckets[i]);  // Delete each pair
        }
    }
    free(t->buckets);  // Free buckets array
    free(t);  // Free the table itself
}

/**
 * Locate bucket index for given key using linear probing.
 *
 *  1. If key is already in table, it returns the index of Pair with the
 *  corresponding key.
 *
 *  2. If key is not in table, it returns the index where a new Pair should be
 *  inserted.
 *
 *  3. If key is not in table and it is not possible to insert a new Pair, it
 *  returns -1.
 *
 * @param   t       Pointer to the Table structure.
 * @param   key     Key string to locate.
 * @return          Index where Pair with key can be found or inserted (-1 if not possible).
 **/
int table_locate(Table *t, const char *key) {
    int bucket = fnv_hash(key) % t->capacity;  // Remove the strlen(key)
    int probe = 0;

    // Stop when:
    //  1. Empty bucket
    //  2. Matching bucket
    //  3. Run out of buckets
    //
    
    while (probe < t->capacity) {
        if (!t->buckets[bucket]) {
            return bucket;  // Empty bucket found
        }
        if (strcmp(t->buckets[bucket]->key, key) == 0) {
            return bucket;  // Matching key found
        }
        // Linear probing: move to the next bucket
        bucket = (bucket + 1) % t->capacity;
        probe++;
    }
    return -1;  // Table is full
}

/**
 * Add key/value Pair to Table structure if the key is not already present.
 * Otherwise, update the value associated with the key.
 *
 * @param   t               Pointer to the Table structure.
 * @param   key             String key of Pair.
 * @param   value           Integer value of Pair.
 **/
void table_insert_or_update(Table *t, const char *key, long value) {
    if ((double)(t->size) / t->capacity >= t->alpha) {
        table_resize(t, t->capacity * 2);  // Double the capacity if load factor exceeded
    }

    int index = table_locate(t, key);
    if (index == -1) {
        return;  // Table is full, insertion failed
    }

    if (t->buckets[index]) {
        t->buckets[index]->value = value;  // Update value
    } else {
        t->buckets[index] = pair_create(key, value);  // Insert new pair
        t->size++;
    }
}

/**
 * Lookup key in Table structure.
 *
 * @param   t               Pointer to the Table structure.
 * @param   key             String Key of Pair.
 * @return  Value associated with key if it is in table, otherwise -1.
 **/
long table_lookup(Table *t, const char *key) {
    int index = table_locate(t, key);
    if (index == -1 || !t->buckets[index]) {
        return -1;  // Key not found
    }
    return t->buckets[index]->value;
}

/**
 * Print all the pairs in the Table structure.
 *
 * @param   t               Pointer to the Table structure.
 * @param   stream          File stream to write to.
 **/
void table_print(Table *t, FILE *stream) {
    for (int bucket = 0; bucket < t->capacity; bucket++) {
        if (t->buckets[bucket])
            pair_print(t->buckets[bucket], stream);
    }
}

/**
 * Resize the current Table structure with the new capacity.
 *
 * @param   t               Pointer to the Table structure.
 * @param   capacity        New capacity of Table structure.
 **/
void table_resize(Table *t, int capacity) {
    Pair **old_buckets = t->buckets;
    int old_capacity = t->capacity;

    t->buckets = calloc(capacity, sizeof(Pair *));
    t->capacity = capacity;
    t->size = 0;  // Reset size, will be recalculated during reinsertion

    for (int i = 0; i < old_capacity; i++) {
        if (old_buckets[i]) {
            table_insert_or_update(t, old_buckets[i]->key, old_buckets[i]->value);  // Reinsert into resized table
            pair_delete(old_buckets[i]);  // Free old pairs
        }
    }
    free(old_buckets);  // Free old buckets array
}
