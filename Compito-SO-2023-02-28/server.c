#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>

#include "header_prodcons.h"
#include "header_msg.h"

void server(int id_queue_server) {

/* TBD: Creare e inizializzare l'oggetto monitor */
    BufferProdCons * b = (BufferProdCons*)malloc(sizeof(BufferProdCons));

    /* TBD: Creare un thread, 
            e fargli eseguire la funzione "visualizza()",
            passandogli in ingresso l'oggetto monitor
     */
    pthread_t thread;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

    pthread_create(&thread,&attr,visualizza,(void*)b);

    for(int i=0; i<NUM_MESSAGGI_PER_SENSORE; i++) {

        int somma_valori = 0;
        int media = 0;

        for(int j=0; j<NUM_COLLETTORI; j++) {

            int id_collettore = j+1;
            int ret;
            messaggio_collettore m;

            /* TBD: Ricevere un messaggio da un collettore, con ricezione selettiva */
            ret=msgrcv(id_queue_server,(void*)&m,sizeof(messaggio_collettore)-sizeof(long),id_collettore,0);
            if(ret<0){
                perror("Errore msgrcv");
                exit(1);
            }
            /* TBD */
            int valore = m.valore;

            printf("[SERVER] Ricevuto valore=%d\n", valore);

            somma_valori += valore;

        }

        media = somma_valori / NUM_COLLETTORI;

        /* TBD: Chiamare la funzione "produci_valore()",
                passandogli la variabile "media"
        */
        produci_valore(b,media);

    }
    /* TBD: Attendere la terminazione del thread, de-allocare il monitor */

    pthread_join(thread,NULL);
    

}

void * visualizza(void * p) {

    for(int i=0; i<NUM_MESSAGGI_PER_SENSORE; i++) {
        /* TBD: Utilizzare la funzione "consuma_valore()" */
        int valore = consuma_valore(p);

        printf("[VISUALIZZA] Valore=%d\n", valore);
    }

    return NULL;
}


void produci_valore(BufferProdCons * b, int valore) {

    /* TBD: Completare questa funzione introducendo la sincronizzazione */
    pthread_mutex_lock(&(b->mutex));
    while(b->stato==PIENO){
        pthread_cond_wait(&(b->cv_prod),&(b->mutex));
    }

    b->valore = valore;
    b->stato = PIENO;

    pthread_cond_signal(&(b->cv_cons));
    pthread_mutex_unlock(&(b->mutex));

}

int consuma_valore(BufferProdCons * b) {

    /* TBD: Completare questa funzione introducendo la sincronizzazione */
    pthread_mutex_lock(&(b->mutex));
    while(b->stato==VUOTO){
        pthread_cond_wait(&(b->cv_cons),&(b->mutex));
    }

    int valore = b->valore;
    b->stato = VUOTO;

    pthread_mutex_unlock(&(b->mutex));
    return valore;
}
