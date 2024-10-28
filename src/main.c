#include "include/status.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  const int DEFAULT_INPUT_BUFFER_SIZE = 16;

  char *input_buffer;
  int   input_buffer_size = DEFAULT_INPUT_BUFFER_SIZE;

  input_buffer = calloc(input_buffer_size, sizeof(char));
  if (input_buffer == NULL) {
    perror("Failed to allocate memory for the buffer");
    return STAT_MEMALLOCERR;
  }

  free(input_buffer);
  return STAT_SUCCESS;
}
