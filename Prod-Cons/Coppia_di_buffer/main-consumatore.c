#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "buffer.h"
#include "semafori.h"

int main(){

    int buf1_id;
    int buf2_id;
    buffer *buf1;  // creazione struct aggiuntiva
    buffer *buf2;  // idem
    int sem_id;

// inizializzazione di una shared memory per buf1_id ("pathname",'id')

    buf1_id = shmget(ftok(".",'a'), sizeof(buffer),0);

    if(buf1_id<0){
        perror("Errore accesso shm buf1");
        exit(1);
    }

    // attacco alla shm di buf1 attraverso buf1_id 
    buf1 = shmat(buf1_id, NULL, 0);

    if(buf1 == (void*)-1){
        perror("Errore attach shm buf1");
        exit(1);
    }

// inizializzazione di una shared memory per buf2

    buf2_id = shmget(ftok(".",'b'),sizeof(buffer),0);

    if(buf2_id<0){
        perror("Erorre accesso shm buf2");
        exit(1);
    }

    // attacco alla shm di bu2 attraverso buf2_id
    buf2 = shmat(buf2_id, NULL ,0);
    if(buf2 == (void*)-1){
        perror("Errore attach shm buf2");
        exit(1);
    }

// inizializzazione id per i semafori

    sem_id = semget(ftok(".",'c'),2,0);

    if(sem_id < 0){
        perror("Errore accesso semafori c");
        exit(1);
    }


// richiamo della funzione consumazione 5 volte

    for(int i=0; i<5; i++){
        int valore = consumazione(sem_id, buf1, buf2);
    }

    exit(0);

}