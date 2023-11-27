#include "prodcons.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

void Produttore(MonitorStreaming *p);
void Consumatore(MonitorStreaming *p);

int main() {
    /* TBD: Creare un oggetto monitor, e avviare i processi produttore e consumatore */
    MonitorStreaming *p;

    key_t key = IPC_PRIVATE;
    int shm_id=shmget(key,sizeof(p),IPC_CREAT|0664);
    if(shm_id<0){
        perror("Errore shmget\n");
        exit(1);
    }
    p=(MonitorStreaming*)shmat(shm_id,0,0);
    if(p==(void*)-1){
        perror("Errore shmat");
        exit(1);
    }
    init_monitor(&(p->m),2);
    inizializza(p);

    pid_t pid;
        pid=fork();
        if(pid==0){
            Produttore(p);
            sleep(1);
            exit(0);
        }else if(pid<0){
            perror("Errore fork1()");
            exit(1);
        }
    

        pid=fork();
        if(pid==0){
            Consumatore(p);
            sleep(1);
        }else if(pid<0){
            perror("Errore fork");
            exit(1);
        }
    

    int tot=DIM*2;
    for(int i=0;i<tot;i++){
        wait(NULL);
    }

    distruggi(p);
    return 0;
}

void Produttore(MonitorStreaming *p) {

    char stringa[20];
    size_t lunghezza;

    char char_chiave = 'a';
    key_t chiave;
    srand(time(NULL));

    for(int i=0; i<10; i++) {

        lunghezza = 1 + rand() % 20;

        for(int j=0; j<lunghezza-1; j++) {
            stringa[j] = 97 + (rand()%26);
        }

        stringa[lunghezza-1] = '\0';
        
        /* TBD */
        chiave = ftok(".",char_chiave);
        char_chiave = char_chiave + 1;


        /* TBD: Chiamare il metodo "produci()" del monitor */
        produci(p,stringa,lunghezza,chiave);
        sleep(1);
    }
}

void Consumatore(MonitorStreaming *p) {

    char stringa[20];
    size_t lunghezza;

    for(int i=0; i<10; i++) {

        /* TBD: Chiamare il metodo "consuma()" del monitor */
        consuma(p,stringa,&lunghezza);
        sleep(1);
    }
}