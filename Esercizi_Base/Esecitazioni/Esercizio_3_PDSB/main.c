#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <time.h>

#include "semafori.h"
#include "procedure.h"

int main(){

    srand(time(NULL));

//
    int shm_id=shmget(IPC_PRIVATE, sizeof(int),IPC_CREAT|0664);
    if(shm_id<0){
        perror("shm error");
        exit(1);
    }
    
    int *p;
    p=(int*)shmat(shm_id,NULL,0);

//
    int sem_id=semget(IPC_PRIVATE,2,IPC_CREAT|0664);
    if(sem_id<0){
        perror("Errore semafori");
        exit(1);
    }

//
    *p=0;

    semctl(sem_id, SPAZIO_DISPONIBILE,SETVAL,1);
    semctl(sem_id,MESSAGGIO_DISPONIBILE,SETVAL,0);

    int pid=fork();
    if(pid==0){
        consumatore(p, sem_id);
        exit(1);
    }

    pid=fork();
    if(pid==0){
        produttore(p,sem_id);
        exit(1);
    }

    wait(NULL);
    printf("primo figlio terminato\n");

    wait(NULL);
    printf("secondo figlio terminato\n");

    semctl(sem_id,0,IPC_RMID);
    shmctl(shm_id,IPC_RMID,0);

    return 0;


}