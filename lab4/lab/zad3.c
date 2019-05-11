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
    int numer; // Ile liczb w przedziale
} odcinek;

int main(int argc, char * argv[]) {
    int pocz = atoi(argv[1]);
    int kon = atoi(argv[2]);
    int ileProcesow = atoi(argv[3]);
    int przedzial = (kon-pocz)/ileProcesow;
    
    int pid, status, fd[2], sum = 0;
    char cPocz[10];
    char cKon[10];
    int fdes, res;
    
    res = mkfifo("IN", 0666);
    if (res < 0) {
    	perror("mkfifo IN error\n");
    }
    fdes = open("IN",O_RDWR);
    if (fdes < 0) {
    	perror("open IN error\n");
    } 
    ,
    for (int i=0; i<ileProcesow; i++) {
    	if (i > 0)
            pocz = pocz + i*przedzial + 1;
        kon = pocz + przedzial;
    	
    	odcinek.pocz = pocz;
    	odcinek.kon = kon;
    	odcinek.numer = i;
    	printf("%d %d %d", odcinek.pocz, odcinek.kon, odcinek.numer);
    	write(fdes, &odcinek, sizeof(odcinek));
    }
    
    for(int i=0; i<ileProcesow; i++) {
        if((pid=fork())==0) {    
            sprintf(cPocz, "%d", pocz);
            sprintf(cKon, "%d", kon);
            execl("./licz", "licz", cPocz, cKon, NULL);
        }
        res = write(fdes, &wynik, sizeof(wynik));
    }
    
    //fdes = open("FIFO", O_RDWR);
    if (fdes < 0) {
    	perror("Error - zad3, open FIFO\n");
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