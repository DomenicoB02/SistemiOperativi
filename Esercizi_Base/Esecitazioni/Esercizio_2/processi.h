#ifndef _PROCESSI_H_
#define _PROCESSI_H_

#include "semafori.h"

#define NUM_PROC 4
#define NUM_ELEM 20
#define MUTEX 0

#define Max 10

void figlio(int *vettore,
            int *buffer,
            int sem_id,
            int elem_init,
            int qta_elem);
    
void padre( int *buffer,
            int sem_id);

#endif // _PROCESSI_H_