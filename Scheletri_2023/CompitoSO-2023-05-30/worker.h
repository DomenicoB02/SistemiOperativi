#ifndef _HEADER_
#define _HEADER_

#include "monitor_signal_continue.h"

#define N_WORKER 4
#define DIM 10
#define ITERAZIONI 5

struct MonitorWorker {

    int vettore_condiviso[DIM];
    int vettori_risultati[N_WORKER][DIM];

    int elaborazioni_completate;
    int elaborazioni_da_completare;

    /* TBD: Aggiungere variabili per la sincronizzazione */
    Monitor m;
};

// costruttore/distruttore
void init_monitor_worker(struct MonitorWorker * p);
void delete_monitor_worker(struct MonitorWorker * p);

// chiamate dal manager
void preleva_risultati(struct MonitorWorker * p, int * vettore);
void scrivi_vettore_condiviso(struct MonitorWorker * p, int * vettore);

// chiamate dai worker
void preleva_vettore_condiviso(struct MonitorWorker * p, int * vettore);
void scrivi_risultati(struct MonitorWorker * p, int * vettore, int id_worker);

void stampa_vettore(int * vettore);

#endif