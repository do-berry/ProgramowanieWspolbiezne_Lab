#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
  static char c;
  int ffifo = mkfifo("MyFIFO", 0666);
  if (ffifo < 0) {
    printf("Error\n");
  } else {
    printf("Ok: %d\n", ffifo);
  }
  int fifoOpen = open("MyFIFO", O_RDWR);
  if (fifoOpen < 0) {
    printf("Error\n");
    exit(0);
  } else {
    printf("Open\n");
  }
  int i = 0;
  do {
    c = '0' + (i++)%10;
    printf("Zapis: %c\n", c);
    ffifo = write(fifoOpen, &c, 1);
  } while (i < 10);
  close(fifoOpen);
}
