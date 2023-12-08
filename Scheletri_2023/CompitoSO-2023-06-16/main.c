#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>

#include "prodcons.h"

void Produttore(/* TBD: completare lo scambio di parametri */);
void Consumatore(/* TBD: completare lo scambio di parametri */);

int main() {

    int id_monitor_buf_singolo = /* TBD: Allocare l'oggetto MonitorBufferSingolo in memoria condivisa */;

    /* TBD: Inizializzare l'oggetto MonitorBufferSingolo */


    int id_coda = /* TBD: Allocare una coda di messaggi */



    /* TBD: Creare un processo figlio, che esegua la funzione "Produttore()" */


    /* TBD: Creare un processo figlio, che esegua la funzione "Consumatore()" */


    /* TBD: Attendere la terminazione dei processi figli */


    /* TBD: Deallocare l'oggetto monitor */


    /* TBD: Deallocare la coda di messaggi */
}


void Produttore(/* TBD: completare lo scambio di parametri */) {

    int numero_elementi = rand() % 10;

    printf("[PRODUTTORE] Totale elementi da inviare: %d\n", numero_elementi);

    /* TBD: Effettuare una produzione su MonitorBufferSingolo con
            la funzione "produzione_buffer_singolo", inserendo "numero_elementi"
     */

    for(int i=0; i<numero_elementi; i++) {
    
        sleep(1);

        int val = rand() % 10;

        printf("[PRODUTTORE] Invio del valore: %d\n", val);


        /* TBD: Inviare il valore "val" tramite la coda di messaggi */

    }
}

void Consumatore(/* TBD: completare lo scambio di parametri */) {

    /* TBD: Effettuare una consumazione su MonitorBufferSingolo con
            la funzione "consumazione_buffer_singolo", prelevando "numero_elementi"
     */

    int numero_elementi = /* TBD */;

    printf("[CONSUMATORE] Totale elementi da ricevere: %d\n", numero_elementi);


    for(int i=0; i<numero_elementi; i++) {

        /* TBD: Ricevere il valore "val" tramite la coda di messaggi */

        int val = /* TBD */;

        printf("[CONSUMATORE] Ricezione del valore: %d\n", val);
    }
}
