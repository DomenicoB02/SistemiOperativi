#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include "header.h"


/*******PROCEDURE PER I SEMAFORI******/


void Wait_Sem(int id_sem, int numsem)     {
       struct sembuf sem_buf;
       sem_buf.sem_num=numsem;
       sem_buf.sem_flg=0;
       sem_buf.sem_op=-1;
       semop(id_sem,&sem_buf,1);   //semaforo rosso
}


  void Signal_Sem (int id_sem,int numsem)     {
       struct sembuf sem_buf;
       sem_buf.sem_num=numsem;
       sem_buf.sem_flg=0;
       sem_buf.sem_op=1;
       semop(id_sem,&sem_buf,1);   //semaforo verde
}

/***********************************************/

void Lettore(Info_Volo *volo, int coda){
        int id_sem;
        for (int i=0; i<NUM_OPERAZIONI; i++) {
                //TODO: accesso alla risorsa secondo soluzione lettori/scrittori, starvation scrittori
                //InizioLettura
                Wait_Sem(id_sem,MUTEXL);
                volo->num_lettori = volo->num_lettori+1;
                if(volo->num_lettori==1){
                        Wait_Sem(id_sem,SYNCH);
                }
                Signal_Sem(id_sem, MUTEXL);
                //TODO: creazione e invio messaggio al visualizzatore

                msg m;
                m.volo=volo->id_volo;
                m.gate=volo->gate;
                msgsnd(coda,&m,sizeof(msg)-sizeof(long),0);
                
                printf("Messaggio inviato\n");
                sleep(1);

                //TODO: rilascio risorsa secondo soluzione lettori/scrittori, starvation scrittori
                //FineLettura
                Wait_Sem(id_sem,MUTEXL);
                volo->num_lettori=volo->num_lettori-1;
                if(volo->num_lettori==0){
                        Signal_Sem(id_sem,SYNCH);
                }
                Signal_Sem(id_sem,MUTEXL);

        }

}

void Scrittore(Info_Volo* volo1, Info_Volo* volo2) {
        int id_sem;

        for (int i=0; i<NUM_OPERAZIONI; i++) {
                //TODO: accesso alle risorse secondo soluzione lettori/scrittori, starvation scrittori 
                Wait_Sem(id_sem,SYNCH);
                //TODO: gate del volo 2 = gate del volo 1
                volo2->gate = volo1->gate;
                //TODO: gate del volo 1 = valore casuale da 1 a 100 
                volo1->gate=1+rand()%100;
                sleep(3);
                //TODO: rilascio  risorse secondo soluzione lettori/scrittori, starvation scrittori 
                Signal_Sem(id_sem,SYNCH);
        }

}


