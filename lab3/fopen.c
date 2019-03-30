#include <stdio.h>
#include <stdlib.h>
#define SIZE 80

int main() {
  int ile;
  FILE *f;
  char buf[SIZE];
  f = fopen("fread.c", "r");
  if (f == NULL) {
    perror("fopen");
    exit(0);
  }
  do {
    ile = fread(&buf, sizeof(buf), 1, f);
    printf("%s\n", buf);
  } while (ile == 1);
  fclose(f);
  return 0;
}
