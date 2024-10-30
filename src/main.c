#include "corelib/core.h"
#include "include/status.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int execution_loop(char *input_buffer, int input_buffer_size);

int main() {
  const int DEFAULT_INPUT_BUFFER_SIZE = 16;

  char *input_buffer;
  int input_buffer_size = DEFAULT_INPUT_BUFFER_SIZE;

  input_buffer = calloc(input_buffer_size, sizeof(char));
  if (input_buffer == NULL) {
    perror("calloc");
    return STAT_MEMALLOCERR;
  }
  terminal_mode_switch(0);

  execution_loop(input_buffer, input_buffer_size);

  terminal_mode_switch(1);
  free(input_buffer);
  return STAT_SUCCESS;
}

int execution_loop(char *input_buffer, int input_buffer_size) {
  int buffer_index = 0;
  char current_char;

  while (1 == 1) {

    if (read(STDIN_FILENO, &current_char, 1) == -1) {
      perror("read");
      break;
    }

    switch (current_char) {
    default: {
      putchar(current_char);
      fflush(stdout);
      break;
    }
    }
  }

  return STAT_SUCCESS;
}
