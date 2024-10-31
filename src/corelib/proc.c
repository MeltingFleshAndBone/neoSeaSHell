#include "../include/status.h"
#include "core.h"
#include <stdio.h>
#include <string.h>

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



  memset(fields, '\x00', word_count);
  return STAT_SUCCESS;
}
