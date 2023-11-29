#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <pthread.h>

#include "pubsub.h"

#define MAX_TOPICS 2
#define MAX_SUBSCRIBERS 2

int code[MAX_TOPICS][MAX_SUBSCRIBERS];

void * gestisci_registrazioni(void * arg);
void * gestisci_messaggi(void * arg);


int main() {

    // inizializzazione lista di code
    for(int i=0; i<MAX_TOPICS; i++) {
        for(int j=0; j<MAX_SUBSCRIBERS; j++) {
            code[i][j] = 0;
        }
    }

/* TBD */
    key_t chiave_coda_registrazioni = ftok(".",'a');
/* TBD: Creare una coda di messaggi di registrazione */
    int id_coda_registrazioni = msgget(chiave_coda_registrazioni,IPC_CREAT|0664);

/* TBD */
    key_t chiave_coda_messaggi = ftok(".",'b');
/* TBD: Creare una coda di messaggi dei publisher */
    int id_coda_messaggi = msgget(chiave_coda_messaggi,IPC_CREAT|0664);


    pthread_t thread[2];
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    /* TBD:
        Creare un thread che esegua la funzione "gestisci_registrazioni".
        Passare come parametro alla funzione gli id delle code.
    */
    pthread_create(&thread[0],&attr,gestisci_registrazioni,(void*)id_coda_registrazioni);
    /* TBD:
        Creare un thread che esegua la funzione "gestisci_messaggi".
        Passare come parametro alla funzione gli id delle code.
     */
    pthread_create(&thread[1],&attr,gestisci_messaggi,(void*)id_coda_messaggi);
    /* TBD: Attendere la terminazione dei 2 thread */

    for(int i=0;i<2;i++){
        pthread_join(thread[i],NULL);
    }

    /* TBD: Deallocare le 2 code di messaggi */
    msgctl(id_coda_messaggi,IPC_RMID,0);
    msgctl(id_coda_registrazioni,IPC_RMID,0);
}


void * gestisci_registrazioni(void * arg) {
    /* TBD: Completare il passaggio di parametri */
    messaggio_registrazione* mr=(messaggio_registrazione*)arg;

    for(int i=0; i<TOTALE_SUBSCRIBER; i++) {

        messaggio_registrazione messaggio;

        /* TBD: Ricevere un messaggio di registrazione */
        int id_coda_registrazioni;
        msgrcv(id_coda_registrazioni,&messaggio,sizeof(messaggio_registrazione)-sizeof(long),0,0);

/* TBD */
        long topic = messaggio.topic;
/* TBD */
        int coda_id = messaggio.coda_id;

        printf("[BROKER] Ricevuto messaggio di registrazione: topic=%ld, id_coda=%d\n", topic, coda_id);


        // aggiungo il subscriber alla lista di code

        if(topic <= 0 || topic > MAX_TOPICS) {
            printf("[BROKER] Topic non valido\n");
            exit(1);
        }

        if(coda_id <= 0) {
            printf("[BROKER] Id coda non valido\n");
            exit(1);
        }

        int trovato = 0;
        for(int i=0; i<MAX_SUBSCRIBERS; i++) {
            if(code[topic-1][i] == 0) {
                code[topic-1][i] = coda_id;
                trovato = 1;
                break;
            }
        }

        if(trovato == 0) {
            printf("[BROKER] Numero massimo di subscriber raggiunto\n");
            exit(1);
        }

    }

    return NULL;
}


void * gestisci_messaggi(void * arg) {
/* TBD: Completare il passaggio di parametri */
    messaggio_valore *mv = (messaggio_valore*)arg;

    for(int i=0; i<TOTALE_MESSAGGI; i++) {

        messaggio_valore messaggio;

        /* TBD: Ricevere un messaggio dai publisher  */

        int id_coda_messaggi;
        msgrcv(id_coda_messaggi,&messaggio,sizeof(messaggio_valore)-sizeof(long),0,0);

/* TBD */
        long topic = messaggio.topic;
/* TBD */        
        int valore = messaggio.val;

        printf("[BROKER] Ricevuto messaggio: topic=%ld, valore=%d\n", topic, valore);



        // invio messaggio a tutti i subscriber registrati al topic

        if(topic <= 0 || topic > MAX_TOPICS) {
            printf("[BROKER] Topic non valido\n");
            exit(1);
        }

        for(int j=0; j<MAX_SUBSCRIBERS; j++) {

            int id_coda = code[topic-1][j];

            if(id_coda != 0) {

                /* TBD: Inviare il messaggio al subscriber in ascolto sulla coda "id_coda" */
                msgsnd(id_coda,&messaggio,sizeof(messaggio_valore)-sizeof(long),0);
            }
        }

    }

    return NULL;
}
