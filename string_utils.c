#include "string_utils.h"

#include <ctype.h>
#include <string.h>

/**
 * Convert all the characters in the string to lowercase.
 *
 * @param   s       String to convert.
 * @return  Pointer to the first character in string.
 **/
char *str_lower(char *s) {
    for (int i = 0; s[i] != '\0'; i++) {
        s[i] = tolower(s[i]);  // Convert each character to lowercase
    }
    return s;  // Return the modified string
}

/**
 * Trim front and back of string of any non-alphanumeric characters.
 *
 * @param   s       String to convert.
 * @return  Pointer to the first alphanumeric character in string.
 **/
char *str_trim(char *s) {
    // Find the first alphanumeric character
    char *start = s;
    while (*start && !isalnum((unsigned char)*start)) {
        start++;
    }

    // Find the last alphanumeric character
    char *end = s + strlen(s) - 1;
    while (end >= start && !isalnum((unsigned char)*end)) {
        end--;
    }

    // Terminate the string after the last alphanumeric character
    *(end + 1) = '\0';

    return start;  // Return the trimmed string
}
