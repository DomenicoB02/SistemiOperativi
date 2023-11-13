#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include "semafori.h"

int main(){
//
    int shm_id = shmget(IPC_PRIVATE,sizeof(int),IPC_CREAT|0664);
    if(shm_id<0){
        perror("Errore shm");
        exit(1);
    }
    //
        int *shm=shmat(shm_id,0,0);
        if(shm==(void*)-1){
            perror("Errore nell'attach della shm");
            exit(1);
        }

        *shm=0;
        printf("Valore iniziale: %d\n",*shm);
//
    int sem_id = semget(IPC_PRIVATE, 1, IPC_CREAT|0664);
    if(sem_id<0){
        perror("Errore sem");
        exit(1);
    }
    //
        semctl(sem_id,0,SETVAL,1);
        printf("Semaforo %d inizializzato ad 1\n",sem_id);

//
    for(int i=0;i<2;i++){
        pid_t pid=fork();
        if(pid<0){
            perror("Errore nella fork)");
            exit(1);
        }else if(pid==0){
            printf("Processo[%d] PID=%d creato\n",i,getpid());
            for(int j=0;j<100;j++){
                Wait_Sem(sem_id,0);

                    printf("Processo %d ha letto\n",i);
                    int temp= *shm;
                    *shm=temp + 1;
                    printf("Processo %d ha incrementato\n",i);
/*DEBUG-------*/    printf("[%d]\n",*shm);
                Signal_Sem(sem_id,0);
            }
            exit(0);
        }
    }

//
    for(int i=0;i<2;i++){
        wait(NULL);
    }

    printf("Il valore finale è: [%d]\n",*shm);

//
    shmctl(shm_id, IPC_RMID, 0);
    semctl(sem_id,0,IPC_RMID);

    return 0;

}