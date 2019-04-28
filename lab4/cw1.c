#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int fildes[2], p2;
  char msg[10], msg2[10];
  if (pipe(fildes) < 0) {
    printf("Error\n");
  }

  if ((p2 = fork()) == 0) {
    close(fildes[0]);
    for (int i = 1; i < 11; i++) {
      sprintf(msg, "%d", i);
      write(fildes[1], msg, sizeof(msg));
      sleep(1);
    }
    close(fildes[0]);
    exit(0);
  }
  close(fildes[1]);
  read(fildes[0], msg2, sizeof(msg));
  printf("%s", msg2);
  close(fildes[0]);

  return 0;
}
