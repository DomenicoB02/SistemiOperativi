#include <stdio.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>

#include "procedure.h"

int main(){

    int k,status,queue;
    pid_t pid;

    //assegnazione coda di comunicazione
    queue=msgget(IPC_PRIVATE,IPC_CREAT|0664);

    // inizializzazione code di servizio
    initServiceQueues();

    // generazione produttore e consumatore
    pid=fork();
    if(pid==0){
        printf("Sono il produttore. Il mio pid %d\n",getpid());
        sleep(2);
        Produttore(queue,"www.unina.it");
        exit(0);
    }else{
        pid=fork();
        if(pid==0){
            printf("Sono il figlio consumatore. Il mio pid %d\n",getpid());
            sleep(1);
            Consumatore(queue);
            exit(0);
        }
    }

    // attesa terminazione
    for(k=0; k<2; k++){
        pid=wait(&status);
        if(pid==-1) perror("Errore");
        else printf("Figlio n.ro %d morto con status %d\n",pid, status);
    }

    // deallocazione code
    msgctl(queue, IPC_RMID, 0);
    removeServiceQueues();
    
    return 1;
}