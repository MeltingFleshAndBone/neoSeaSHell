#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

void print_handle(int type) {
  /* Print the command prompt handle
   * Displays username, hostname, and current directory in a formatted prompt
   * Supports two display types:
   *   type 0: Full prompt with colors - username@hostname:cwd\n$
   *   type 1: Simple prompt - username$
   * Colors used:
   *   Green: username@hostname
   *   Blue: current working directory 
   *   Yellow: $ prompt
   * 
   * Params:
   *   type: Integer specifying prompt type (0 or 1)
   * Returns: void */

  // For some reason it doesn't let me use const int...
  #define HOST_NAME_MAX 64
  #define PATH_MAX 4096


  char *string;
  char hostname[HOST_NAME_MAX + 1];
  char cwd[PATH_MAX];
  struct passwd *pw = getpwuid(getuid());
  
  if (pw == NULL) {
    perror("getpwuid");
    return;
  }

  // Get current working directory
  if (getcwd(cwd, sizeof(cwd)) == NULL) {
    perror("getcwd");
    return;
  }
  
  // Get hostname
  if (gethostname(hostname, sizeof(hostname)) != 0) {
    perror("gethostname");
    return;
  }

  switch (type) {
    case 0: {
      // Format: username@hostname:cwd\n$
      // Colors: username/hostname in green, cwd in blue, $ in yellow
      size_t needed = strlen(pw->pw_name) + strlen(hostname) + strlen(cwd) + 50;
      string = malloc(needed);
      if (string == NULL) {
        perror("malloc");
        return;
      }
      snprintf(string, needed, "\033[32;1m%s@%s\033[0m:\033[34;1m%s\033[0m\n\033[33;1m$\033[0m ", 
              pw->pw_name, hostname, cwd);
      break;
    }
    case 1: {
      // Simple prompt with just username and $
      size_t needed = strlen(pw->pw_name) + 30;
      string = malloc(needed);
      if (string == NULL) {
        perror("malloc");
        return;
      }
      snprintf(string, needed, "\033[32;1m%s\033[0m \033[33;1m$\033[0m ", pw->pw_name);
      break;
    }
    default: {
      string = "\033[33;1m$\033[0m ";
    }
  }

  printf("%s", string);
  fflush(stdout);
  
  if (type == 0 || type == 1) {
    free(string);
  }
}
