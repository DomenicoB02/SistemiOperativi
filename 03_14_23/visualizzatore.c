#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "header.h"

void printer(int coda, long v) {

    int i;
    for (i = 0; i < (NUM_LETTORI*NUM_OPERAZIONI)/2; i++){
        msg mess;
        //TODO: ricezione del messaggio per il volo: "v"
        int ret =msgrcv(coda,&mess,sizeof(msg)-sizeof(long),0,0);
        printf("Il volo %ld ha cambiato gate; nuovo gate: %d\n",v,mess.gate);
    }
}

int main() {


    //TODO: creazione coda
    key_t c_coda = ftok(".",'a');
    // ..
    int coda=msgget(c_coda,IPC_CREAT|0664);
    if(coda<0){
        perror("Errore msgget");
        exit(1);
    }
    //TODO: creazione 2 processi visualizzatori, uno per volo 1 e uno per volo 2
    Info_Volo *volo1, *volo2;
    pid_t pid;
    int i;
    for (i=0;i<2;i++){
        pid=fork();
        if(pid==0){
            if(i%2==0){
                printer(coda,1);
                exit(0);
            }else{
                printer(coda,2);
                exit(0);
            }
        }
    }

    for(i=0;i<2;i++){
        wait(NULL);
    }
    //TODO: rimozione coda
    msgctl(coda,IPC_RMID,0);
    return 0;
}