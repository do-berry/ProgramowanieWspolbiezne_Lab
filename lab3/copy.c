// works correctly!
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#define SIZE 512

int main(int argc, char *argv[]) {
  char buf[SIZE];
  int file1 = open(argv[1], O_RDONLY);
  int file2 = open(argv[2], O_RDWR|O_CREAT,(~022)&0666);

  read(file1, buf, SIZE);
  write(file2, buf, SIZE);

  close(file1);
  close(file2);

  return 0;
}
