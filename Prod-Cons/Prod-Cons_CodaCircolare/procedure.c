#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>

#include "procedure.h"
#include "semafori.h"


void produttore(struct prodcons * p, int ds_sem) {
    Wait_Sem(ds_sem, SPAZIO_DISPONIBILE);
    Wait_Sem(ds_sem, MUTEX_P);
    
    sleep(2);
    
    //procedure
    p->buffer[p->testa] = rand() % 100;
    
    printf("Il valore prodotto = %d\n", p->buffer[p->testa]);
    
    p->testa = (p->testa+1) % DIM_BUFFER;
    
    Signal_Sem(ds_sem, MUTEX_P);
    
    Signal_Sem(ds_sem, MESSAGGIO_DISPONIBILE);
}

void consumatore(struct prodcons * p, int ds_sem) {
    Wait_Sem(ds_sem, MESSAGGIO_DISPONIBILE);
    Wait_Sem(ds_sem, MUTEX_C);
    
    sleep(2);
    
    printf("Il valore consumato = %d\n", p->buffer[p->coda]);
    //procedure
    p->coda = (p->coda + 1) % DIM_BUFFER;
    
    Signal_Sem(ds_sem, MUTEX_C);
    
    Signal_Sem(ds_sem, SPAZIO_DISPONIBILE);
}
