#include "../include/status.h"
#include "core.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int proc_manager(char *buffer) {
  int word_count = 0;
  fflush(stdout);

  for (int i = 0; buffer[i] != '\x00'; i++) {
    // Getting the number of words by counting N of spaces
    if (buffer[i] == ' ') {
      word_count++;
    }
  }

  char *fields[word_count + 1];

  split(buffer, fields);

  fields[word_count + 1] = NULL;

  expand(fields);

  if (strcmp(fields[0], "exit") == 0) {
    exit(0);
  } else if (strcmp(fields[0], "cd") == 0) {
    if (fields[1] == NULL) {
      // Will make this go to `~` eventually
      fprintf(stderr, "No path specified.\n");
      return STAT_CHDIRERR;
    }
    if (chdir(fields[1]) != 0) {
      perror("cd");
      return STAT_CHDIRERR;
    }
    return STAT_SUCCESS;
  }

  pid_t pid = fork();
  if (pid < 0) {
    // Fork failed
    perror("Fork");
    return 0;
  } else if (pid > 0) {
    // Parent process
    wait(NULL); // Wait for the child process to finish
  } else {
    // Child process

    {
      execvp(fields[0], fields); // Execute the process with arguments
      // If execvp returns, it must have failed
      perror("execvp");
      exit(0);
    }
  }

  memset(fields, '\x00', word_count);
  return STAT_SUCCESS;
}
