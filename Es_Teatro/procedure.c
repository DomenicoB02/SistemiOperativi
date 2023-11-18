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

void produttore(posto* p, int id_sem, int num, int j){

    int indice=0;
    Wait_Sem(id_sem, SPAZIO_DISPONIBILE);
        Wait_Sem(id_sem,MUTEX_P);

            while(indice<=DIM && p[j].stato[indice]!=LIBERO){
                indice++;
            }

            p[j].stato[indice]=INUSO;
        
        Signal_Sem(id_sem,MUTEX_P);

        p[j].id_cliente=getpid();
        p[j].stato[indice]=OCCUPATO;
        printf("Il posto n.ro %d è occupato da %d\n",j,p[j].id_cliente);

    Signal_Sem(id_sem, MESSAGGIO_DISPONIBILE);

}


void consumatore(posto* p, int id_sem, int j){

    int indice=0;
    Wait_Sem(id_sem,MESSAGGIO_DISPONIBILE);
        Wait_Sem(id_sem,MUTEX_C);

            while(indice<=DIM && p[j].stato[indice]!=OCCUPATO){
                indice++;
            }
            p[j].stato[indice]=INUSO;

        Signal_Sem(id_sem,MUTEX_C);

        p[j].stato[indice]=LIBERO;
        printf("La prenotazione per il posto %d occupata da %d è stata cancellata\n",j,p[j].id_cliente);


    Signal_Sem(id_sem,SPAZIO_DISPONIBILE);

}

void visualizza(posto* p){

    for(int i=0; i<POSTI; i++){
        if(p[i].stato==LIBERO){
            printf("Posto %d NON prenotato\n", i);
        }else if(p[i].stato==OCCUPATO){
            printf("Posto %d prenotato da %d\n",i,p[i].id_cliente);
        }
    }

}