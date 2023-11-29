#ifndef _HEADER_PRODCONS_H_
#define _HEADER_PRODCONS_H_

#include <pthread.h>

typedef struct {

    /* TBD: Aggiungere ulteriori variabili per la sincronizzazione */
    pthread_mutex_t mutex;

    pthread_cond_t ok_prod;
    pthread_cond_t ok_cons;
    
    int valore;
    int stato;

} BufferProdCons;

#define VUOTO 0
#define PIENO 1

int produci_valore(BufferProdCons * b, int valore);
int consuma_valore(BufferProdCons * b);
void * visualizza(void *);

#endif