#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include "header.h"


int main(){
     //TODO: completare richiesta shared memory ed inizializzazione
     key_t c_mem=ftok(".",'a');
     // ...
     int shm_id=shmget(c_mem,sizeof(Info_Volo),IPC_CREAT|0664);
     if(shm_id<0){
          perror("Errore shm");
          exit(1);
     }

     Info_Volo *volo1, *volo2, *volo;
     volo1=(Info_Volo*)shmat(shm_id,0,0);
     volo2=(Info_Volo*)shmat(shm_id,0,0);
     //TODO inizializzare id_volo pari a 1 per volo1 e pari a 2 per volo2

     volo1->id_volo=1;
     volo2->id_volo=2;

     //TODO: compleare richiesta semafori ed inizializzazione
     key_t c_sem =IPC_PRIVATE;
     // ...
     int id_sem=semget(c_sem,2,IPC_CREAT|0664);
     if(id_sem<0){
          perror("Errore semget");
          exit(1);
     }

     semctl(id_sem,MUTEXL,SETVAL,1);
     semctl(id_sem,SYNCH,SETVAL,1);
     //TODO: compleatare richiesta coda messaggi
     key_t c_coda=ftok(".",'b');
     // ...
     int msg_id=msgget(c_coda,IPC_CREAT|0664);
     if(msg_id<0){
          perror("Errore");
          exit(1);
     }
     
     //TODO generazione tramite fork di scrittore e 4 lettori, 2 per il volo 1 e 2 per il volo 2
     pid_t pid;

     //lettori per volo1
     for(int i=0;i<2;i++){
          pid=fork();
          if(pid==0){
               Lettore(volo1,msg_id);
               exit(0);
          }else if(pid<0){
               perror("Errore fork()");
               exit(1);
          }
     }

     //lettori per volo2
     for(int i=0;i<2;i++){
          pid=fork();
          if(pid==0){
               Lettore(volo2,msg_id);
               exit(0);
          }else if(pid<0){
               perror("Errore fork()");
               exit(1);
          }
     }

     // scrittore
     pid=fork();
     if(pid==0){
          srand((time(NULL))*getpid());
          Scrittore(volo1,volo2);
          exit(0);
     }else if(pid<0){
          perror("Errore fork scrittore");
          exit(1);
     }

     //TODO generazione tramite fork/exec del visualizzatore
     pid=fork();
     if(pid==0){
          execl("./visualizzatore","./visualizzatore",NULL);
          perror("Se sei qui c'è un problema");
          exit(1);
     }

     //TODO: attesa terminazione dei "numprocessi"  figli
     int numprocessi = NUM_LETTORI+2;
     for(int i=0;i<numprocessi;i++){
          wait(NULL);
     }
     //TODO: Deallocazione risorse
     shmctl(shm_id,IPC_RMID,0);
     semctl(id_sem,0,IPC_RMID);
     msgctl(msg_id,IPC_RMID,0);

     return 0;
}
