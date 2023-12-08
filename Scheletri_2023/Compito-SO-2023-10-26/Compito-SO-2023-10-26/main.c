#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "header.h"

void * produttore(void *);
void * consumatore(void *);

int main() {

    pthread_t thread_consumatore;
    pthread_t thread_produttori[3];

    /* TBD: Creare un oggetto monitor, e inizializzarlo con init_monitor() */

    /* TBD: Creare 3 thread produttori, chiamando la funzione produttore() */

    /* TBD: Creare 1 thread consumatore, chiamando la funzione consumatore() */


    /* TBD: Attendere la terminazione dei 3 thread produttori */

    /* TBD: Attendere la terminazione del thread consumatore */

    /* TBD: Disattivare e deallocare l'oggetto monitor */
}


void * produttore(void * p) {

    printf("Avvio thread produttore...\n");


    for(int i=0; i<5; i++) {

        sleep(1);

        // genera carattere casuale tra "a" e "z"
        char carattere = 97 + (rand() % 26);

        /* TBD: Chiamare il metodo "produzione()", passando l'oggetto monitor e
         *      la variabile "carattere" */
    }

    return NULL;
}

void * consumatore(void * p) {

    printf("Avvio thread consumatore...\n");


    int totale_consumazioni = 0;

    while(totale_consumazioni < 15) {

        int occupati = 1;
        
        if(totale_consumazioni < 13) {

            printf("CONSUMATORE: In attesa di elementi disponibili...\n");

            occupati = /* TBD: Chiamare il metodo "attesa()" */

            printf("CONSUMATORE: %d elementi disponibili\n", occupati);
        }

        for(int j=0; j<occupati; j++) {

            char carattere;
            
            carattere = /* TBD: Chiamare il metodo "consumazione()" */
        }

        totale_consumazioni += occupati;
    }

    return NULL;
}
