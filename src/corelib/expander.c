#include "../include/status.h"
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

struct passwd *get_user_info() {
  uid_t uid = getuid();
  struct passwd *pw = getpwuid(uid);

  if (pw == NULL) {
    perror("getpwuid");
    return NULL;
  }

  return pw;
}

int split(char *string, char *dest[]) {
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
  struct passwd *pw = get_user_info();
  if (pw == NULL) {
    return -1;
  }

  for (int i = 0; buffer[i] != NULL; i++) {
    // Handle home directory expansion
    if (strcmp(buffer[i], "~") == 0) {
      char *homeDir = pw->pw_dir;
      buffer[i] = malloc(strlen(homeDir) + 1);
      if (buffer[i] == NULL) {
        perror("malloc");
        return -1;
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
          return -1;
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
          return -1;
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
        return -1;
      }
      strcpy(buffer[i], user);
    }
  }

  return STAT_SUCCESS;
}
