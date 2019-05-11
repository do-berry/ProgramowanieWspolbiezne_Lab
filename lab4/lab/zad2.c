#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

struct {
    int pocz;// początek przedzialu
    int kon; // koniec przedzialu
    int ile; // Ile liczb w przedziale
} wynik;

int main(int argc, char * argv[]) {
    int pocz = atoi(argv[1]);
    int kon = atoi(argv[2]);
    int ileProcesow = atoi(argv[3]);
    int przedzial = (kon-pocz)/ileProcesow;
    
    int pid, status, fd[2], sum = 0;
    char cPocz[10];
    char cKon[10];
    int fdes, res;
    
    if (mkfifo("FIFO", 0666) <0) {
    	perror("Error - zad2, mkfifo\n");
    }
    
    for(int i=0; i<ileProcesow; i++) {
        if((pid=fork())==0) {
            if (i > 0)
            	pocz = pocz + i*przedzial + 1;
            kon = pocz + przedzial;
            sprintf(cPocz, "%d", pocz);
            sprintf(cKon, "%d", kon);
            execl("./licz", "licz", cPocz, cKon, NULL);
        }
    }
    
    fdes = open("FIFO", O_RDWR);
    if (fdes < 0) {
    	perror("Error - zad2, open FIFO\n");
    	exit(0);
    }

    while ((pid = wait(&status)) > 0){
        printf("Proces %d zakonczony status %d\n", pid, WEXITSTATUS(status));
        read(fdes, &wynik, sizeof(wynik));
        sum += wynik.ile;
        printf("Wynik: %d\n", wynik.ile);
    }
     
    printf("Znaleziono %d liczb pierwszych\n", sum);
    close(fdes);
    
    return 0;
}