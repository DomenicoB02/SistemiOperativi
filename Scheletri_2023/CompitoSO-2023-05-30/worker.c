#include <stdio.h>
#include <unistd.h>

#include "worker.h"

// costruttore/distruttore

void init_monitor_worker(struct MonitorWorker * p) {

    /* TBD: Inizializzare il sotto-oggetto monitor e le variabili di stato */
}

void delete_monitor_worker(struct MonitorWorker * p) {

    /* TBD: Deallocare il sotto-oggetto monitor */
}


// chiamate dal manager

void preleva_risultati(struct MonitorWorker * p, int * vettore) {

    /* TBD: Completare la sincronizzazione */

    int vettore_medie[DIM];

    for(int i=0; i<DIM; i++) {
        vettore_medie[i] = 0;
    }
    
    for(int j=0; j<N_WORKER; j++) {

        for(int i=0; i<DIM; i++) {
            vettore_medie[i] += p->vettori_risultati[j][i];
        }
    }

    for(int i=0; i<DIM; i++) {
        vettore_medie[i] /= N_WORKER;

        vettore[i] = vettore_medie[i];
    }

}


void scrivi_vettore_condiviso(struct MonitorWorker * p, int * vettore) {

    /* TBD: Completare la sincronizzazione */

    for(int i=0; i<DIM; i++) {
        p->vettore_condiviso[i] = vettore[i];
    }

}


// chiamate dai worker

void preleva_vettore_condiviso(struct MonitorWorker * p, int * vettore) {

    /* TBD: Completare la sincronizzazione */

    for(int i=0; i<DIM; i++) {
        vettore[i] = p->vettore_condiviso[i];
    }

}

void scrivi_risultati(struct MonitorWorker * p, int * vettore, int id_worker) {

    /* TBD: Completare la sincronizzazione */

    for(int i=0; i<DIM; i++) {
        p->vettori_risultati[id_worker][i] = vettore[i];
    }

}


void stampa_vettore(int * vettore){

    printf("[ ");
    for(int i=0; i<DIM; i++) {
        printf("%d ", vettore[i]);
    }
    printf("]\n");
}

