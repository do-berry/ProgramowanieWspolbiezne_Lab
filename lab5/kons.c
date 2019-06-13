#include <stdio.h>
#include <mqueue.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "common.h"

int main(int argc, char *argv[])
{
    int i, res, num = 0;
    //int id =0;
    unsigned int prior;
    mqd_t mq;
    struct mq_attr attr;
    ms_type msg;
    prior = 10;
    if (argc < 2)
    {
        printf("Uzycie: kons numer\n");
        exit(0);
    }
    num = atoi(argv[1]);
    // Utworzenie kolejki komunikatow ----------------

    mq = mq_open("/Kolejka", O_RDWR);

    mq_getattr(mq, &attr);

    if (mq == -1)
    {
        perror("Kolejka ");
        exit(0);
    }
    for (i = 0; i < 10; i++)
    {
        mq_getattr(mq, &attr); //  Status kolejki
        printf("%ld komunikatow\n", attr.mq_curmsgs);
        res = mq_receive(mq, (char *)&msg, sizeof(msg), &prior);
        if (res == -1)
            perror("Blad odczytu z mq");
        else
            printf("Konsument: %d odebral: %s\n", num, msg.text);
        sleep(1);
    }
    mq_close(mq);
    //mq_unlink(MQ_NAME);
}