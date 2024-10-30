#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

void terminal_mode_switch(int mode) {
  struct termios tty;

  // Get the current terminal attributes
  if (tcgetattr(STDIN_FILENO, &tty) < 0) {
    perror("tcgetattr");
    exit(EXIT_FAILURE);
  }

  switch (mode) {
  case 0:                            // RAW mode
    tty.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
    tty.c_cc[VMIN] = 1;              // Minimum number of characters to read
    tty.c_cc[VTIME] = 0;             // No timeout
    break;

  case 1:                           // COOKED mode
    tty.c_lflag |= (ICANON | ECHO); // Enable canonical mode and echo
    break;

  default:
    fprintf(stderr, "Invalid mode. Use 0 for RAW and 1 for COOKED.\n");
    return;
  }

  // Set the new attributes
  if (tcsetattr(STDIN_FILENO, TCSANOW, &tty) < 0) {
    perror("tcsetattr");
    exit(EXIT_FAILURE);
  }
}
