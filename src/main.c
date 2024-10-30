#include "corelib/core.h"
#include "include/control_seq.h"
#include "include/status.h"
#include <string.h>
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
  const float DEFAULT_BUFFER_GROWTH_RATE = 1.25;

  int buffer_index = 0;
  char current_char;

  while (1 == 1) {

    if (read(STDIN_FILENO, &current_char, 1) == -1) {
      perror("read");
      break;
    }

    switch (current_char) {
      case ASCII_LF: {
        // Null terminating it
        input_buffer[buffer_index + 1] = '\x00';
        putchar('\n');

        // Here one would call the parser and then the process manager
        
        fflush(stdout);
        
        for (int i = 0; input_buffer[i] != '\x00'; i++) {
          printf("%c", input_buffer[i]);
        }
        putchar('\n');
        fflush(stdout);
        
        memset(input_buffer, 0, buffer_index);
        buffer_index = 0;
        break;
      } 

      default: {
        if (input_buffer_size >= buffer_index) {
          // Buffer is too small, will resize it now
          input_buffer_size = (int)(input_buffer_size * DEFAULT_BUFFER_GROWTH_RATE);
          // casting the result to int to avoid issues with realloc
          
          input_buffer = realloc(input_buffer, input_buffer_size);
          if (input_buffer == NULL) {
            perror("realloc");
            break;
          }
        }

        input_buffer[buffer_index++] = current_char;

        putchar(current_char);
        fflush(stdout);
        break;
      }
    }
  }

  return STAT_SUCCESS;
}
