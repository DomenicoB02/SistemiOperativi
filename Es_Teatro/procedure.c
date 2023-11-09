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

void produttore(struct prodcons* p, int id_sem){

    int disp=POSTI;
    int num_posti=0;

    Wait_Sem(id_sem,SPAZIO_DISPONIBILE);
    Wait_Sem(id_sem,MUTEX_P);
    
    int sleeptime=(rand()%4)+1;
    sleep(sleeptime);
    
    num_posti=(rand()%4)+1;
    if(num_posti>disp+1){
        perror("Disponibilità esaurita\n");
        exit(1);
    }else{
        while(disp>0 && p->stato_posto[disp] != LIBERO){
            disp=disp-num_posti;
        }

        for(int i=disp; i<(disp+num_posti); i++){
            p->stato_posto[i]=INUSO;
        }
    }
    Signal_Sem(id_sem,MUTEX_P);

    for(int i=disp; i<(disp+num_posti);i++){
        p->stato_posto[i]=OCCUPATO;
        p->buffer[i].id_cliente=getpid();
        p->buffer[i].stato = p->stato_posto[i];
        printf("Il cliente %d ha prenotato il posto %d\n",
                p->buffer[disp].id_cliente,          i);
    }

    Signal_Sem(id_sem,MESSAGGIO_DISPONIBILE);

}


void consumatore(struct prodcons* p, int id_sem){

    int disp=POSTI;
    int indice=0;
    int j=0;

    Wait_Sem(id_sem,MESSAGGIO_DISPONIBILE);
    Wait_Sem(id_sem,MUTEX_C);

    while(disp>0 && p->stato_posto[disp] != OCCUPATO){
        disp--;
    }

    while(p->stato_posto[disp] == OCCUPATO && 
          p->buffer[disp].id_cliente==p->buffer[disp-1].id_cliente){
            disp--;
            j++;
    }

    Signal_Sem(id_sem,MUTEX_C);

    printf("Il processo %d ha occupato %d posti \n",p->buffer[disp].id_cliente,j+1);
    Signal_Sem(id_sem,SPAZIO_DISPONIBILE);

}


void visualizza(struct prodcons* p){

    for(int j=0;j<POSTI;j++){
        if(p->buffer[j].stato==OCCUPATO){
            printf("posto %d occupato dal processo %d\n",j+1,p->buffer[j].id_cliente);
        }else{
            printf("posto %d libero\n",j+1);
        }
    }

}