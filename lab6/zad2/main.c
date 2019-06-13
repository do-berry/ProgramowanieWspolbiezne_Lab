// Program producenta-konsumenta (C) J. Ulasiewicz 2013
// Demonstruje dzialanie pamieci dzielonej i semaforow
// Kompilacja gcc prod_kons.c -o prod_kons -lrt
#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BSIZE     10   // Rozmiar bufora
#define LSIZE    80   //  Dlugosc linii



typedef struct {
 int pocz;
 int kon ;
 int suma;
 } dane_t;

 typedef struct {
 int wymiar;
 dane_t dane[BSIZE];
 } buf_t; 

int pierwsza(int n)
// Funkcja zwraca 1 gdy n jest liczbą pierwsza 0 gdy nie
{ 
    int i,j=0;
    for(i=2;i*i<=n;i++) {
        if(n%i == 0 || n==0 || n==1) return 0;    
    }
    return 1;
} 

int liczbaPierwszych(int a, int b)
{
    int suma = 0;
    for(int i = a; i <= b; i++)
    {
        suma = suma+=pierwsza(i);
    }
    return suma;
}   


int main(int argc,char *argv[]) {
 int i,stat,k, pid, size, fd,res, status;
 buf_t  *wbuf ;
 char c;
 // Utworzenie segmentu ---------------------------
 shm_unlink("bufor");
 fd=shm_open("bufor", O_RDWR|O_CREAT , 0774);
 if(fd == -1){
   perror("open"); _exit(-1);
 }

 printf("fd: %d\n",fd);
 size = ftruncate(fd,sizeof(buf_t));  
 if(size < 0) {perror("trunc"); _exit(-1); }
 // Odwzorowanie segmentu fd w obszar pamieci procesow
 wbuf = (buf_t *)mmap(0, sizeof(buf_t)
         ,PROT_READ|PROT_WRITE,MAP_SHARED, fd, 0);
 if(wbuf == NULL) {perror("map");  _exit(-1); }

 // Inicjacja obszaru --------------------------------
 wbuf-> wymiar = 0;
//  -----Tworzenie procesow -------------
 if(fork() == 0) { // Producent
    for(i=0;i<atoi(argv[2]);i++) {
        	int pid, status;
        int result = 0;
        int numbers = atoi(argv[1]);
        int howManyProcesses = atoi(argv[2]);
        int numbersInProcess = numbers/howManyProcesses;
        int currentRange = 0;   
        for(int i = 0; i < howManyProcesses; i++)
        {
            if((pid = fork()) == 0 ){
                int p = numbersInProcess*(i);
                int k = numbersInProcess*(i+1);
                int wynik1 = liczbaPierwszych(p, k);
                wbuf->dane[i].pocz =  p;
                wbuf->dane[i].kon = k;
                wbuf->dane[i].suma = wynik1; 
            }
        }
     }     
     _exit(i);
 }
    while((pid = wait(&status)) > 0)
    {
        printf("Proces %d zakonczony status %d\n", pid, WEXITSTATUS(status));
    }  

    int i2;
    int wynikC = 0;
    for(int i2 = 0; i2 < BSIZE; i2++)
    {
        printf("Przedział nr %d, poczatek: %d, koniec: %d, wynik: %d\n", i2,wbuf->dane[i2].pocz,wbuf->dane[i2].kon,wbuf->dane[i2].suma);
        wynikC+=wbuf->dane[i2].suma;
    }
    printf("Wynik calkowity: %d\n", wynikC);

return 1;
}