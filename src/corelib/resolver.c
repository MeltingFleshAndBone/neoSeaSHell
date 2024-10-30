#include "../include/status.h"
#include <stdio.h>
#include <string.h>

int split(char *string, char *dest[]) {
    char *token;
    int count = 0;

    // Use strtok to get the first token
    token = strtok(string, " ");

    // Continue tokenizing until no more tokens are found
    while (token != NULL) {
        dest[count++] = token;  // Store the token in the destination array
        token = strtok(NULL, " ");  // Get the next token
    }

    // Return the number of tokens found
    return count;
}


int expand(char *buffer[]) {
  /* This is supposed to split the buffer into tokens,
   * I *might* use regex, or just hardcode it all */
  
  return STAT_SUCCESS;
}
