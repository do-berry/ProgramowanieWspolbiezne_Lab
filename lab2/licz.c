#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int pierwsza(int n) {
  // 1 : pierwsza; 0 : nie
  int i, j = 0;
  for (i = 2; i*i <= n; i++) {
    if (n%i == 0) {
      return 0;
    }
  }
  return 1;
}

int main(int argc, char * argv[]) {
  int dol, gora, nr;
  int suma = 0;

  for (int i = dol; i <= gora; i++) {
    if (pierwsza(i) == 1) {
      suma++;
    }
  }

  printf("Proces potomny sie konczy.");
  _exit(nr);
}
