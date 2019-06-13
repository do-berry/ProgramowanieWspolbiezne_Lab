//---------------------------------------------------------------------------------
// Producent / konsument  proces wysylajacy komunikaty do kolejki     
// Odbiera program mq_rcv
// Kompilacja:   gcc mq_snd.c -o mq_snd -lrt   
// Uruchomienie: ./mq_snd numer
// Gdy zamontujemy koleki komunikatow w kat /dev/mqueue to mozna nimi manipulowaÄ
// uzywajÄc poleceĹ ls,...
// mkdir /dev/mqueue
// mount -t mqueue none /dev/mqueue
// ----------------------------------------------------------------------------------
#include <stdio.h>
#include <mqueue.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "common.h"

int main(int argc, char *argv[]) {
    int i;
    int kroki;
    int res;
    mqd_t mq;
    ms_type msg;
    // printf("test\n");
    mq=mq_open("/Kolejka",O_RDWR);

    if(mq < 0) { 
      perror("prod.c /Kolejka");
      exit(-1);
    }

    msg.pnr = atoi(argv[1]);
    kroki = atoi(argv[2]);
    // printf("kroki: %d\n", kroki);
    // printf("nr: %d", msg.pnr);
    
    msg.type = 1;

    for(i=0; i < kroki ;i++) {
      sprintf(msg.text,"Proces %d komunikat %d ",msg.pnr, i);
      res = mq_send(mq,(char *)&msg,sizeof(msg),10);
      printf("%s\n",msg.text);
      sleep(1);
    }
    mq_close(mq); 
  } 
 