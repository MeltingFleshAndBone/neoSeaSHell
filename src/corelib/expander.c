#include "../include/status.h"
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

struct passwd *get_user_info() {
  /* Get current user information
   * Retrieves password database entry for current user
   * Returns: Pointer to passwd struct on success, NULL on failure */

  uid_t uid = getuid();
  struct passwd *pw = getpwuid(uid);

  if (pw == NULL) {
    perror("getpwuid");
    return NULL;
  }

  return pw;
}

int split(char *string, char *dest[]) {
  /* Split string into array of tokens
   * Splits input string on spaces into array of token pointers
   * Modifies original string by inserting null terminators
   * Params:
   *   string: Input string to split
   *   dest: Array to store token pointers
   * Returns: Number of tokens found */

  char *token;
  int count = 0;

  // Use strtok to get the first token
  token = strtok(string, " ");

  // Continue tokenizing until no more tokens are found
  while (token != NULL) {
    dest[count++] = token;
    token = strtok(NULL, " ");
  }

  return count;
}

int expand(char *buffer[]) {
  /* Expand shell variables and special characters
   * Handles expansion of:
   *   ~ - Current user's home directory
   *   ~user - Named user's home directory
   *   $HOME - Home directory from environment
   *   $USER - Current username
   * Modifies array in place, allocating new strings as needed
   * Params:
   *   buffer: Null-terminated array of strings to expand
   * Returns:
   *   STAT_SUCCESS on success
   *   STAT_MEMALLOCERR on memory allocation error
   *   STAT_EXPANSIONERR on expansion error */

  struct passwd *pw = get_user_info();
  if (pw == NULL) {
    return STAT_EXPANSIONERR;
  }

  for (int i = 0; buffer[i] != NULL; i++) {
    // Handle home directory expansion
    if (strcmp(buffer[i], "~") == 0) {
      char *homeDir = pw->pw_dir;
      buffer[i] = malloc(strlen(homeDir) + 1);
      if (buffer[i] == NULL) {
        perror("malloc");
        return STAT_MEMALLOCERR;
      }
      strcpy(buffer[i], homeDir);
    }
    // Handle ~user expansion
    else if (buffer[i][0] == '~' && buffer[i][1] != '\0') {
      struct passwd *targetpw;
      char *username = buffer[i] + 1;
      targetpw = getpwnam(username);
      if (targetpw != NULL) {
        buffer[i] = malloc(strlen(targetpw->pw_dir) + 1);
        if (buffer[i] == NULL) {
          perror("malloc");
          return STAT_MEMALLOCERR;
        }
        strcpy(buffer[i], targetpw->pw_dir);
      }
    }
    // Handle $HOME expansion
    else if (strcmp(buffer[i], "$HOME") == 0) {
      char *homeDir = getenv("HOME");
      if (homeDir != NULL) {
        buffer[i] = malloc(strlen(homeDir) + 1);
        if (buffer[i] == NULL) {
          perror("malloc");
          return STAT_MEMALLOCERR;
        }
        strcpy(buffer[i], homeDir);
      }
    }
    // Handle $USER expansion
    // I'll remove this eventually when I implement actual env vars
    else if (strcmp(buffer[i], "$USER") == 0) {
      char *user = pw->pw_name;
      buffer[i] = malloc(strlen(user) + 1);
      if (buffer[i] == NULL) {
        perror("malloc");
        return STAT_MEMALLOCERR;
      }
      strcpy(buffer[i], user);
    }
  }

  return STAT_SUCCESS;
}
