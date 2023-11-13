#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>

#include "semafori.h"
#include "processi.h"

int main(){

    int vett_id;
    int buffer_id;
    int sem_id;
    int *vettore;
    int *buffer;

    vett_id = shmget(IPC_PRIVATE,sizeof(int)*NUM_ELEM,IPC_CREAT|0664);
    if(vett_id<0){
        perror("Errore vett_id nella shm");
        exit(1);
    }
    vettore=(int*)shmat(vett_id,0,0);
    if(vettore==(void*)-1){
        perror("Errore nell'attach del vettore");
        exit(1);
    }

    srand(time(NULL));
    for(int i=0; i<NUM_ELEM;i++){
        vettore[i]=rand()%Max;
        printf("valore n.r [%d]\n",vettore[i]);
    }

    buffer_id = shmget(IPC_PRIVATE,sizeof(int),IPC_CREAT|0664);
    if(buffer_id<0){
        perror("Errore buffer_id nella shm");
        exit(1);
    }
    buffer=(int*)shmat(buffer_id,0,0);
    if(buffer==(void*)-1){
        perror("Errore nel attach del buffer");
        exit(1);
    }

    *buffer=Max;

    sem_id=semget(IPC_CREAT,1,IPC_CREAT);
    if(sem_id<0){
        perror("Errore nella creazione del semaforo");
        exit(1);
    }
    semctl(sem_id,0,SETVAL,1);
        
    
    for(int i=0;i<NUM_PROC;i++){
        pid_t pid=fork();
            if(pid<0){
                perror("Errore fork");
                exit(1);
            }
            if(pid==0){
                printf("Processo figlio n.ro <%d>\n",i+1);
                figlio( vettore,
                        buffer,
                        sem_id,
                        i*5,
                        5);

                exit(0);
            }
    }

    padre(  buffer,
            sem_id);
    

    semctl(sem_id,0,IPC_RMID);
    shmctl(vett_id,IPC_RMID,0);
    shmctl(buffer_id,IPC_RMID,0);

    return 0;

}