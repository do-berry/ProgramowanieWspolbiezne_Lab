#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

struct {
    int pocz;// początek przedzialu
    int kon; // koniec przedzialu
    int ile; // Ile liczb w przedziale
} wynik;

int pierwsza(int n)
{ 
    int i,j=0;
    for(i=2;i*i<=n;i++) {
        if(n%i == 0 || n==0 || n==1) return 0;    
    }
    return 1;
}

int ilePierwszych(int a, int b)
{
    int suma = 0;
    for(int i = a; i <= b; i++)
    {
        suma+=pierwsza(i);
    }
    return suma;
}  

int main(int argc, char * argv[]) {
    int pocz = atoi(argv[1]);
    int kon = atoi(argv[2]);
    int ileProcesow = atoi(argv[3]);
    
    int pid, status, fd[2], sum = 0;
    
    pipe(fd);
    for(int i=0; i<ileProcesow; i++) {
        if((pid=fork())==0) {
            pocz =  pocz+i*((kon-pocz)/ileProcesow);
            if(i != ileProcesow-1)
                kon = pocz+(i+1)*((kon-pocz)/ileProcesow)-1;

	    // do struktury
	    wynik.pocz = pocz;
	    wynik.kon = kon;
	    wynik.ile = ilePierwszych(pocz, kon);
	            
            write(fd[1], &wynik, sizeof(wynik));
            printf("%d %d %d\n", wynik.pocz, wynik.kon, wynik.ile);
            exit(i);
        }
    }

    while ((pid = wait(&status)) > 0){
        printf("Proces %d zakonczony status %d\n", pid, WEXITSTATUS(status));
        read(fd[0], &wynik, sizeof(wynik));
        sum += wynik.ile;
    }
     
    printf("Znaleziono %d liczb pierwszych\n", sum);
    close(fd[1]);
    
    return 0;
}