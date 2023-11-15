#include "semafori.h"

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int Wait_Sem(int sem_id, int numsem){

    int err;
    struct sembuf sem_buf;

    sem_buf.sem_num=numsem;
    sem_buf.sem_flg=0;
    sem_buf.sem_op=-1; // semaforo rosso

    err = semop(sem_id, &sem_buf, 1);
    if(err<0){
        perror("Errore Wait");
        exit(1);
    }

    return err;

}

int Signal_Sem(int sem_id, int numsem){

    int err;
    struct sembuf sem_buf;

    sem_buf.sem_num=numsem;
    sem_buf.sem_flg=0;
    sem_buf.sem_op=1; // semaforo verde

    err = semop(sem_id, &sem_buf, 1);
    if(err<0){
        perror("Errore Signal");
        exit(1);
    }

    return err;

}