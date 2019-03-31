#include <stdio.h>
#include <sys/wait.h> 
#include <stdlib.h> 
#include <unistd.h> 
void main(int argc, char * argv[]){
	int status, pid; 
	for (int j = 1; j < argc-1; j++) {
		if(fork() == 0) {
			/* Proces potomny ---*/
			for(int i=0; i<atoi(argv[j+1]);i++) {
        			printf("Potomny %d, krok: %d\n", j, i); 
   				sleep(1); 
			} 
      			exit(j); 
  		}
	}
 	/* Proces macierzysty */
	for (int j = 1; j < argc-1; j++) {
 		printf("Macierzysty = %d\n", getpid());
	}
	for (int j = 1; j < argc-1; j++) { 
 		pid = wait(&status);
 		printf("Proces %d zakonczony status: %d\n", pid, WEXITSTATUS(status));
	}
}
