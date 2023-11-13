#include "processi.h"
#include "semafori.h"

#include <sys/wait.h>
#include <limits.h>
#include <unistd.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

void figlio(int *vettore,
            int *buffer,
            int sem_id,
            int elem_init,
            int qta_elem){

    int minimo=Max;
   

        for(int i=elem_init;i<elem_init+qta_elem;i++){

            if(vettore[i]<minimo){
                minimo=vettore[i];
            }
            
        }
        printf("Il minimo locale è: [%d]\n",minimo);

    
    Wait_Sem(sem_id, 0);
        if(minimo<*buffer){
            *buffer=minimo;
        }
    Signal_Sem(sem_id, 0);
}

void padre( int *buffer,
            int sem_id){

    for(int i=0;i<NUM_PROC;i++){
        wait(NULL);
    }

    printf("Il minimo assoluto è [%d]\n",*buffer);

}