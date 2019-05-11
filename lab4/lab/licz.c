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

int pierwsza(int n) {
  int i, j = 0;
  for (i = 2; i*i <= n; i++) {
    if (n%i == 0) {
      return 0;
    }
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
  int suma = 0;
  int pocz = atoi(argv[1]);
  int kon = atoi(argv[2]);
  
  suma = ilePierwszych(pocz, kon);
  
  // do struktury
  wynik.pocz = pocz;
  wynik.kon = kon;
  wynik.ile = suma;
  
  printf("Dla procesu: %d, %d, %d\n", pocz, kon, suma);
  
  int fdes, res;
  
  res = mkfifo("FIFO", 0666);
  fdes = open("FIFO",O_RDWR);  
  if(fdes < 0) {
    perror("Error - licz, open FIFO\n"); 
    exit(0); 
  }
  res = write(fdes, &wynik, sizeof(wynik));
  close(fdes);
  
  exit(0);
}

