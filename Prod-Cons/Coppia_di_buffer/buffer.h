#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "semafori.h"


/*
Questo tipo di struct vale solo in tale esercizio, se 
dovessimo utilizzare delle strutture potremmo utilizzare la variabile
valore come puntatore ad un altra struct
*/
typedef struct{
    int valore;
    int stato;
}buffer;

void produzione(int sem_id, buffer *buf1, buffer *buf2, int valore);
int consumazione(int sem_id, buffer *buf1, buffer *buf2);

// per utilizzare la variabile stato 
#define LIBERO 0
#define INUSO 1
#define OCCUPATO 2

// variabili semaforo
#define SPAZIO_DISPONIBILE 0
#define MESSAGGIO_DISP 1

/* 
    no MUTEX_C e MUTEX_P dato che c'è solo un produttore e un consumatore
*/

#endif // _BUFFER_H_