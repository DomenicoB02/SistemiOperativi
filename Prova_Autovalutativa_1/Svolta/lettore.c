#include "buffer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>

int main(){

    printf("[%d] Avvio lettore\n", getpid());

    key_t chiave_queue = ftok(".",'q');
    int queue = msgget(chiave_queue, IPC_CREAT|0664);

    key_t chiave_shm = ftok(".",'m');
    int shm_id = shmget(chiave_shm, sizeof(buffer), 0644);
    if(shm_id<0){
        perror("Errore creazione shared memory");
        exit(1);
    }

    buffer *b = shmat(shm_id, NULL, 0);
    if(b == (void*)-1){
        perror("Errore attach shared memory");
        exit(1);
    }

    key_t sem_chiave = ftok(".",'s');
    int sem_id = semget(sem_chiave, 4, 0644);
    if(sem_id<0){
        perror("Errore semget()");
        exit(1);
    }

    srand(getpid());
    for(int i=0; i<NUMERO_LETTURE; i++){
        char val_1 = '\0';
        char val_2 = '\0';

        leggi_buffer(b, sem_id, &val_1, &val_2, queue);
    }

    return 0;

}