#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>

#include "header_msg.h"

void sensore(int id_sensore, int id_queue_collettore) {

    srand(getpid());

    for(int i=0; i<NUM_MESSAGGI_PER_SENSORE; i++) {

        messaggio_sensore m;

        int valore = (rand() % 10) + 10;

        /* TBD: Inviare "valore" mediante messaggio */
        m.id_sensore=id_sensore;
        m.valore=valore;

        int ret = msgsnd(id_queue_collettore,&m,sizeof(messaggio_sensore)-sizeof(long),0);
        if(ret<0){
            perror("Errore");
            exit(1);
        }

        printf("[SENSORE] Inviato valore=%d\n", valore);


        sleep(3);
    }
}