#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>

#include "procedure.h"

#define NUM_PRODUTTORI 1
#define NUM_CONSUMATORI 1

int main(){

    key_t shm_key = IPC_PRIVATE;
    int id_shm = shmget(shm_key, sizeof(struct prodcons), IPC_CREAT | 0664);

    if(id_shm<0){
        perror("Errore SHMGET");
        exit(1);
    }

    struct prodcons *pc = shmat(id_shm, 0, 0);

    if(pc == (void*) -1){
        perror("Errore SHMAT");
        exit(1);
    }

    init_monitor(&(pc->m), 2);
    pc->buffer_libero = 1;
    pc->buffer_occupato = 0;

    pid_t pid;

    for(int i=0;i<NUM_CONSUMATORI; i++){

        pid = fork();

        if(pid==0){

            printf("Figlio consumatore di pid [%d]\n", getpid());
            int valore = consuma(pc);
            printf("Valore consumato [%d]", valore);
            exit(0);
        }
        else if (pid<0){
            perror("Errore FORK cons");
            exit(0);
        }
    }

    for(int i=0;i<NUM_PRODUTTORI; i++){
        srand(time(NULL));
        pid = fork();
        if(pid==0){
            
            printf("Figlio Produttore di pid [%d]\n", getpid());
            int valore = rand() % 10;
            produci(pc, valore);
            printf("valore prodotto [%d]\n", valore);
            exit(0);
        }
        else if (pid<0){
            perror("Errore FORK prod");
            exit(1);
        }
    }

    for (int i=0;i<NUM_CONSUMATORI + NUM_PRODUTTORI; i++){
        wait(NULL);
    }

    remove_monitor(&(pc->m));
    shmctl(id_shm, IPC_RMID, 0);

    return 0;
}