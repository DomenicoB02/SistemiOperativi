#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "buffer.h"
#include "semafori.h"

int main(){

    int buf1_id;
    int buf2_id;
    buffer *buf1;
    buffer *buf2;
    int sem_id;

// inizializzazione di un id per buf1
    buf1_id = shmget(ftok(".",'a'),sizeof(buffer), IPC_CREAT | 0664);

    if(buf1_id < 0){
        perror("Errore creazione shm buf1");
        exit(1);
    }

    // attacco alla memoria di buf1
    buf1 = shmat(buf1_id, NULL, 0);
    if(buf1 == (void*)-1){
        perror("Errore attach shm buf1");
        exit(1);
    }
// inizializzazione per un id di buf2
    buf2_id = shmget(ftok(".",'b'), sizeof(buffer), IPC_CREAT|0664);

    if(sem_id<0){
        perror("Errore creazione semafori");
        exit(1);
    }

    // attacco alla memoria di buf2
    buf2 = shmat(buf2_id, NULL,0);
    if(buf2 == (void*)-1){
        perror("Errore attach shm buf2");
        exit(1);
    }


// inizializzazione di una chiave per i semafori
    sem_id = semget(ftok(".",'c'), 2, IPC_CREAT|0664);
    if(sem_id<0){
        perror("Errore nel semaforo");
        exit(1);
    }
    // attraverso semctl dò un valore iniziale ai semafori
    semctl(sem_id, SPAZIO_DISPONIBILE,SETVAL,2);
    semctl(sem_id,MESSAGGIO_DISP, SETVAL, 0);

// inizializzo i buff di stato a LIBERO
    buf1->stato = LIBERO;
    buf2->stato = LIBERO;

// creo una fork per il figlio produttore
    pid_t pid1 =fork();

    if(pid1<0){
        perror("Errore creazione produttore");
        exit(1);
    }else if(pid1==0){
        //figlio produttore attivato attraverso execl
        execl("./main-produttore","main-produttore",NULL);
    }


// creo una fork per il figlio consumatore
    pid_t pid2 = fork();

    if(pid2<0){
        perror("Errore creazione consumatore");
        exit(1);
    }else if(pid2==0){
        //figlio consumatore attivato attraverso l'execl
        execl("./main-consumatore","main-consumatore",NULL);
    }

// la wait serve ad attendere che tutti i figli siano creati
    for(int i=0;i<2;i++){
        wait(NULL);
    }

// deallocazione delle variabili in shm
    shmctl(buf1_id, IPC_RMID,NULL);
    shmctl(buf2_id, IPC_RMID, NULL);
    semctl(sem_id, 0, IPC_RMID);


}