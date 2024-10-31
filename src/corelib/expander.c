#include "../include/status.h"
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int split(char *string, char *dest[]) {
  char *token;
  int count = 0;

  // Use strtok to get the first token
  token = strtok(string, " ");

  // Continue tokenizing until no more tokens are found
  while (token != NULL) {
    dest[count++] = token;     // Store the token in the destination array
    token = strtok(NULL, " "); // Get the next token
  }

  // Return the number of tokens found
  return count;
}

int expand(char *buffer[]) {
  uid_t uid = getuid();
  struct passwd *pw = getpwuid(uid);

  if (pw == NULL) {
    perror("getpwuid");
    return -1;
  }

  for (int i = 0; buffer[i] != NULL; i++) {
    fflush(stdout);
    if (strcmp(buffer[i], "~") == 0) {
      char *homeDir = pw->pw_dir;
      // Allocate memory for the expanded path
      buffer[i] = malloc(strlen(homeDir) + 1);
      if (buffer[i] == NULL) {
        perror("malloc");
        return -1;
      }
      strcpy(buffer[i], homeDir); // Copy the home directory path
      fflush(stdout);
    }
  }

  return STAT_SUCCESS;
}
