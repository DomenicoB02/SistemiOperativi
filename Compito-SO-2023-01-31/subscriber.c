#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <time.h>

#include "pubsub.h"

void subscriber(int id_coda_registrazioni, long topic);

int main() {

    pid_t pid;
    srand(time(NULL)*getpid());
    /* TBD */
    key_t chiave_coda_registrazioni = ftok(".",'A');
    /* TBD: Creare una coda di messaggi di registrazione */
    int id_coda_registrazioni = msgget(chiave_coda_registrazioni,IPC_CREAT|0660);
    if(id_coda_registrazioni<0){
        perror("Errore");
        exit(1);
    }

    for(int i=0; i<NUM_SUBSCRIBERS_PER_TOPIC; i++) {

        printf("[SUBSCRIBER] Avvio processo subscriber su topic 1\n");

        /* TBD: 
            Creare un processo figlio, che esegua la funzione "subscriber".
            Passare come parametri lo ID della coda per le registrazioni, e il valore TOPIC1.
        */
        pid=fork();
        if(pid==0){
            subscriber(id_coda_registrazioni,TOPIC1);
            exit(0);
        }
    }


    for(int i=0; i<NUM_SUBSCRIBERS_PER_TOPIC; i++) {

        printf("[SUBSCRIBER] Avvio processo subscriber su topic 2\n");

        /* TBD: 
            Creare un processo figlio, che esegua la funzione "subscriber".
            Passare come parametri lo ID della coda per le registrazioni, e il valore TOPIC2.
        */
        pid=fork();
        if(pid==0){
            subscriber(id_coda_registrazioni,TOPIC2);
            exit(0);
        }
    }


    printf("[SUBSCRIBER] Attesa terminazione processi figli\n");

    /* TBD: Attendere la terminazione dei processi figli */
    for(int i=0;i<NUM_SUBSCRIBERS_PER_TOPIC*2;i++){
        wait(NULL);
    }

}

void subscriber(int id_coda_registrazioni, long topic) {
    
    /* TBD */
    key_t chiave_coda_messaggi_subscriber = ftok(".",'C');
    /* TBD: Creare una coda di messaggi privata del subscriber */
    int id_coda_messaggi_subscriber = msgget(chiave_coda_messaggi_subscriber,IPC_CREAT|0660);
    if(id_coda_messaggi_subscriber<0){
        perror("Errore");
        exit(1);
    }

    messaggio_registrazione registrazione;

    /* TBD: 
        Inviare un messaggio di registrazione al broker.
        Includere nel messaggio lo ID della coda di messaggi privata.
    */
    int ret;

    registrazione.topic=topic;
    registrazione.id_coda=id_coda_messaggi_subscriber;
    ret=msgsnd(id_coda_registrazioni,(void*) &registrazione,sizeof(messaggio_registrazione)-sizeof(long),0);
    if(ret<0){
        perror("Errore msgsnd");
        exit(1);
    }

    for(int i=0; i<NUM_MESSAGGI*NUM_PUBLISHERS_PER_TOPIC; i++) {

        messaggio_valore messaggio;

        /* TBD: Ricevere un messaggio dal broker */
        ret=msgrcv(id_coda_messaggi_subscriber,(void*)&messaggio,sizeof(messaggio_valore)-sizeof(long),topic,0);
        if(ret<0){
            perror("Errore msgrcv");
            exit(1);
        }
        /* TBD */
        int valore = messaggio.valore;

        printf("[SUBSCRIBER] Ricevuto messaggio: topic=%ld, valore=%d\n", topic, valore);

    }

    /* TBD: Deallocare la coda di messaggi privata del subscriber */
    msgctl(id_coda_messaggi_subscriber,IPC_RMID,0);

}

