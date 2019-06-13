#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#define SIZE 4
#define LSIZE 80
#define KROKI 5
#define SLEEP 1
#define MAX 8
int head, tail, count = 0;
char bufor[SIZE][LSIZE];
pthread_mutex_t mutex;
pthread_t tid[MAX];
int wynik[MAX];

typedef struct {
	int pocz;
	int kon;
	int numer;
	int wynik;
} par_t;

int czyPierwsza(int x) {
	int i;
    	for (i = 2; i * i <= x; i++) {
        	if ((x % i) == 0) {
        		return 0;
        	}
    	}
    	return 1;
}

void * licz(par_t * msg) {
	int start, stop, numer, i, suma = 0;
	
	pthread_mutex_lock(&mutex);
	start = msg->pocz;
	stop = msg->kon;
	numer = msg->numer;
	printf("%d %d %d\n", start, stop, numer);
	pthread_mutex_unlock(&mutex);
	
	for (i = start; i <= stop; i++) {
		suma += czyPierwsza(i);
	}
	
	msg->wynik = suma;
	return (&wynik[numer]);
}

int main(int argc, char * argv[]) {
	int start = atoi(argv[1]);
	int stop = atoi(argv[2]);
	int ileWatkow = atoi(argv[3]);
	int ileLiczbPierwszych = 0;
	if (ileWatkow > MAX) {
		ileWatkow = MAX;
	}
	int zakres = stop - start + 1;
	int delta = zakres/ileWatkow;
	par_t msg[ileWatkow];
	pthread_mutex_init(&mutex, NULL);
	
	printf("Start: %d, stop: %d, dla %d watkow\n", start, stop, ileWatkow);
	printf("Zakres: %d, delta: %d\n", zakres, delta);
	
	for (int i = 0; i < ileWatkow; i++) {
		pthread_mutex_lock(&mutex);
		msg[i].pocz = start + (delta * i);
		msg[i].kon = start + (delta * (i + 1)) - 1;
		msg[i].numer = i;
		pthread_mutex_unlock(&mutex);
		
		printf("Utworzony watek %d: %d - %d\n", i, msg[i].pocz, msg[i].kon);
    		pthread_create(&tid[i], NULL, (void *)licz, (void *)&msg[i]);
    	}
    	
    	for (int i = 0; i < ileWatkow; i++) {
    		pthread_join(tid[i], (void *)&msg[i]);
    		printf("Watek %d sie konczy, wynik = %d\n", i, msg[i].wynik);
    		ileLiczbPierwszych += msg[i].wynik;	
    	}
    	printf("Watki zakonczone, liczb pierwszych: %d\n", ileLiczbPierwszych);
	
	return 0;
}

