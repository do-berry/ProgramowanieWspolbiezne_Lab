#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char * argv[]) {
  int dol = atoi(argv[1]);
  int gora = atoi(argv[2]);
  int procesy = atoi(argv[3]);
  int start, stop, pid, status;
  char num[10];
  char num2[10];
  char num3[10];

  int przedzial = gora/procesy;

  for (int i = 0; i < procesy; i++) {
    if (i == 0){
      start = 1;
      stop = przedzial;
    } else {
      start += przedzial;
      stop += przedzial;
    }

    if ((pid == fork()) == 0) {
      sprintf(num, "%d", start);
			sprintf(num2, "%d", stop);
			sprintf(num3, "%d", i);
			execl("~/PW_exercises/lab2/licz", "licz", num, num2, num3, NULL);
    }
  }
  printf("Proces macierzysty PID %d \n", getpid());
  for(int j = 0; j < procesy; j++)
	{
      pid = wait(&status);
      printf("Proces %d zakonczony. status %d\n", pid, WEXITSTATUS(status));
	}
  // TO DO
}
