// correctly implemented
#include <stdio.h>
#include <stdlib.h>
#define SIZE 50

int main(int argc, char * argv[]) {
  char buf[SIZE];
  FILE * file1, * file2;
  file1 = fopen(argv[1],"r");
  file2 = fopen(argv[2],"w");

  fread(buf, sizeof(char), SIZE, file1);
  fwrite(buf, sizeof(char), SIZE, file2);

  fclose(file1);
  fclose(file2);

  return 0;
}
