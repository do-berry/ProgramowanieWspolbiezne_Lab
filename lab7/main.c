#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#define SIZE 4
#define LSIZE 80
#define KROKI 5
#define SLEEP 1
int head, tail, count = 0;
char bufor[SIZE][LSIZE];
pthread_mutex_t mutex;
pthread_cond_t empty, full;

void * producent(void * arg) {
	int nr, i;
	int cnt = 1;
	nr = (intptr_t) arg; 			// nr producenta
	printf("Producent %d\n - start", nr);
	for (i = 0; i < KROKI; i++) {
		pthread_mutex_lock(&mutex);
        	while (count >= SIZE) {
            		printf("Producent %d: czeka\n", nr);
            		pthread_cond_wait(&empty, &mutex);
        	}
        	sprintf(bufor[head], "Producent: %d, krok: %d", nr, i);
        	printf("Producent %d, licznik = %d, na poz: %d wstawil: %s\n", nr, count, head, bufor[head]);
        	head = (head + 1) % SIZE;
        	count++;
        	pthread_cond_signal(&full);
        	pthread_mutex_unlock(&mutex);
        	sleep(SLEEP);
        	cnt++;
	}
	return 0;
}

void * konsument(void * arg) {
	int nr, i;
    	nr = (intptr_t) arg;				// nr konsumenta
    	printf("Konsument: %d\n - start", nr);
    	for (i = 0; i < KROKI; i++) {
	        pthread_mutex_lock(&mutex); 
        	while (count <= 0) {
	            printf("Konsument%d: czeka\n", nr);
        	    pthread_cond_wait(&full, &mutex);
        	}
        	printf("Konsument %d, licznik = %d, z poz: %d pobral: %s\n", nr, count, tail, bufor[tail]);
        	tail = (tail + 1) % SIZE;
        	count--;       	
        	pthread_cond_signal(&empty);
        	pthread_mutex_unlock(&mutex);
        	sleep(SLEEP);
    	}
    	return 0;
}

int main(int argc, char * argv[]) {
	int ileProd = atoi(argv[1]);
	int ileKons = atoi(argv[2]);
	pthread_t producenci[ileProd];
	pthread_t konsumenci[ileKons];
	
	printf("Producentow: %d, konsumentow: %d\n", ileProd, ileKons);
	
	int nprod, nkons, i, res;
    	pthread_mutex_init(&mutex, NULL);
    	pthread_cond_init(&empty, NULL);
    	pthread_cond_init(&full, NULL);
    	
    	for (int i = 0; i < ileProd; i++) {
    		pthread_create(&producenci[i], NULL, producent,(void *)((intptr_t)i));
    	}
    	
    	for (int i = 0; i < ileKons; i++) {
    		pthread_create(&konsumenci[i], NULL, konsument,(void *)((intptr_t)i));
    	}
    	
    	for (i = 0; i < ileProd; i++) {
        	pthread_join(producenci[i], NULL);
    	}

    	for (i = 0; i < ileKons; i++) {
        	pthread_join(konsumenci[i], NULL);
    	}
	
	return 0;
}
