#include "table.h"
#include "string_utils.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WHITESPACE  " \t\r\n"

int main() {
    double alpha = 0.5;  // Load factor for the hash table

    Table *t = table_create(0, alpha);  // Create a new hash table
    char buffer[BUFSIZ];  // Buffer to hold each line of input

    /* Read input and insert or update frequency counts in table */
    while (fgets(buffer, BUFSIZ, stdin)) {
        char *token = strtok(buffer, WHITESPACE);  // Tokenize the input line
        while (token) {
            char *word = str_trim(str_lower(token));  // Convert to lowercase and trim
            if (strlen(word) > 0) {  // Ensure word is not empty
                long current_count = table_lookup(t, word);  // Lookup current frequency
                if (current_count == -1) {
                    current_count = 0;  // Word not found, set initial count to 0
                }
                table_insert_or_update(t, word, current_count + 1);  // Update frequency
            }
            token = strtok(NULL, WHITESPACE);  // Get next word
        }
    }

    table_print(t, stdout);  // Print the table to stdout
    table_delete(t);  // Clean up and free memory

    return 0;
}
