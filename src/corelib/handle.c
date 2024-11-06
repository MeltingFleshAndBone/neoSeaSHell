
#include <stdio.h>
void print_handle(int type) {
  char *string;

  switch (type) {
    case 0: {
      string = "\033[33;1m$\033[0m ";
    }
  }

  printf("%s", string);
  fflush(stdout);

}
