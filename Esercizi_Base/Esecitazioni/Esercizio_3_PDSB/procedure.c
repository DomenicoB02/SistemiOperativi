#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "procedure.h"
#include "semafori.h"

void produttore(int *p, int sem_id){

    Wait_Sem(sem_id, SPAZIO_DISPONIBILE);

    sleep(2);

    *p=rand()%100;
    printf("Il valore prodotto = %d\n", *p);

    Signal_Sem(sem_id, MESSAGGIO_DISPONIBILE);

}

void consumatore(int *p, int sem_id){

    Wait_Sem(sem_id, MESSAGGIO_DISPONIBILE);

    sleep(2);
    printf("Il valore consumato è = %d\n", *p);

    Signal_Sem(sem_id, SPAZIO_DISPONIBILE);

}