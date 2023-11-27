#include "prodcons.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>


void inizializza(MonitorStreaming * p) {
    /* TBD: Inizializzare il monitor */
        p->testa=0;
        p->coda=0;
        p->num_elementi=0;
        for(int i=0;i<DIM;i++){
            p->vettore[i].dimensione=0;
            p->vettore[i].produttore=0;
            p->vettore[i].chiave=0;
        }
}


void produci(MonitorStreaming * p, char * stringa, size_t lunghezza, key_t chiave) {

    /* TBD: Completare il metodo, con la sincronizzazione */
    enter_monitor(&(p->m));
    if(p->num_elementi == lunghezza){
        wait_condition(&(p->m),COND_PROD);
    }


    printf("Avvio produzione...\n");

    sleep(1);
/* TBD: Creare una nuova shared memory, su cui copiare la stringa */
    int shm_id = shmget(chiave,20,IPC_CREAT|0644);
    if(shm_id<0){
        perror("Errore");
        exit(1);
    }
    char * stringa_shm=(char*)shmat(shm_id,0,0);
    if(stringa_shm==(void*)-1){
        perror("Errore");
        exit(1);
    }

    /* TBD */ 
    p->vettore[p->testa].dimensione = lunghezza;
    /* TBD */ 
    p->vettore[p->testa].chiave = chiave;
    /* TBD */ 
    p->vettore[p->testa].produttore = getpid();

    strcpy(stringa_shm, stringa);   // Copia della stringa

    printf("Produzione completata: %s (%zu char, key=%x)\n", stringa_shm, lunghezza, chiave);
    
    int ret=shmdt(stringa_shm);
    if(ret<0){
        perror("Errore detach");
        exit(1);
    }

    p->num_elementi++;
    p->testa=(p->testa +1)%DIM;
    signal_condition(&(p->m),COND_CONS);
    leave_monitor(&(p->m));
}

void consuma(MonitorStreaming * p, char * stringa, size_t * lunghezza) {

    /* TBD: Completare il metodo, con la sincronizzazione */
    enter_monitor(&(p->m));
    if(p->num_elementi==0){
        wait_condition(&(p->m),COND_CONS);
    }
    
    printf("Avvio consumazione...\n");
    sleep(1);
    
    /* TBD */
    pid_t produttore = p->vettore[p->coda].produttore;
    /* TBD */
    *lunghezza = p->vettore[p->coda].dimensione;
    /* TBD */
    key_t chiave = p->vettore[p->coda].chiave;
/* TBD: Accedere alla stringa su shared memory */
    int shm_id=shmget(chiave,20,0644);
    if(shm_id<0){
        perror("Errore shm_id");
        exit(1);
    }
    char *stringa_shm = (char*)shmat(shm_id,0,0);
    if(stringa_shm==(void*)-1){
        perror("Errore attach");
        exit(1);
    }

    strcpy(stringa, stringa_shm);   // Copia della stringa

    printf("Consumazione completata: %s (%zu char, key=%x)\n", stringa, *lunghezza, chiave);

    int ret=shmdt(stringa_shm);
    if(ret<0){
        perror("errore nel detach");
        exit(1);
    }
    p->num_elementi--;
    p->coda=(p->coda+1)%DIM;
    signal_condition(&(p->m),COND_PROD);
    leave_monitor(&(p->m));
}

void distruggi(MonitorStreaming * p) {
    /* TBD: Completare il metodo */
    remove_monitor(&(p->m));
}