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

void produttore(posto* p, int ds_sem, int pidProcess, int num, int* disp){
    Wait_Sem(ds_sem, MUTEX);
        int indice=0;

        while((indice <= POSTI) && (p[indice].stato != LIBERO)){
            indice++;
        }
        for(int i=indice; i<(indice+num); i++){
            p[indice].stato = INUSO;
        }
        

        for(int i=indice; i<=(indice+num);i++){
            p[i].id_cliente=pidProcess;
            p[i].stato=OCCUPATO;
            printf("Il cliente [%d] ha prenotato il posto %d\n",pidProcess,i);
        }
        
       
        Signal_Sem(ds_sem, MUTEX);
        exit(0);
}

void consumatore(posto* p, int ds_sem){
    sleep(1);
    Wait_Sem(ds_sem,MUTEX);

    for(int i=0;i<POSTI;i++){
        if(p[i].stato==LIBERO){
            printf("posto: %d libero\n",i);
        }else if(p[i].stato==OCCUPATO){
            printf("posto: %d occupato da %d\n",i,p[i].id_cliente);
        }else if(p[i].stato==INUSO){
            printf("posto %d in aggiornamento\n",i);
        }
    }
    Signal_Sem(ds_sem,MUTEX);
}