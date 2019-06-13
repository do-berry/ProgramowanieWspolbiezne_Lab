// Kompilacja: cc wyslij.c -o wyslij -lrt
#include <stdio.h>
#include <mqueue.h>
#include <unistd.h>

int main(int argc, char * argv[]) {
    int kom, res;
    mqd_t mq;
    struct mq_attr attr;
    /* Utworzenie kolejki komunikatow -----------------*/
    attr.mq_msgsize = sizeof(kom);
    attr.mq_maxmsg = 4;
    attr.mq_flags = 0;
    mq_unlink("/Kolejka");
    mq = mq_open("/Kolejka", O_RDWR | O_CREAT, 0660, & attr);  
    if(mq < 0) { 
      perror("prod.c /Kolejka");
      
    } 
    
    mq_close(mq);   
    return 0;
}