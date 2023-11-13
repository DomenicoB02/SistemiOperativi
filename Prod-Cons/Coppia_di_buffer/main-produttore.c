#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "buffer.h"
#include "semafori.h"

int main(){

    int buf1_id;
    int buf2_id;
    buffer *buf1;
    buffer *buf2;
    int sem_id;

// inizializzazione di buf1_id per la shm
    buf1_id = shmget(ftok(".",'a'),sizeof(buffer),0);

    if(buf1_id < 0){
        perror("Errore accesso shm buf1");
        exit(1);
    }
    // attacco alla shm di buf1
    buf1 = shmat(buf1_id, NULL, 0);

    if(buf1 == (void*)-1){
        perror("Errore attach shm buf1");
        exit(1);
    }

// inizializzazione di buf2_id
    buf2_id = shmget(ftok(".",'b'),sizeof(buffer),0);

    if(buf2_id<0){
        perror("Errore accesso shm buf2");
        exit(1);
    }
    // attacco alla shm di buf2
    buf2 = shmat(buf2_id, NULL, 0);

    if(buf2 == (void*)-1){
        perror("Errore attach shm buf2");
        exit(1);
    }

// inizilizzazione di un id per i semafori
    sem_id = semget(ftok(".",'c'), 2, 0);

    if(sem_id < 0){
        perror("Errore accesso semafori");
        exit(1);
    }




// procedure normali con chiamata alla produzione 5 volte
    srand(time(NULL));
    for(int i=0;i<5;i++){
        int valore = rand()%10;
        produzione(sem_id, buf1, buf2, valore);
    }

    exit(0);

}