#include "procedure.h"
#include <stdio.h>


void produci(struct prodcons *pc, int valore){

    enter_monitor(&(pc->m));
    printf("ingresso monitor - Produzione\n");

    if(pc->buffer_occupato == 1){
        printf("Sospensione - Produzione\n");
        wait_condition(&(pc->m), VARCOND_PRODUTTORI);
        printf("Riattiazione - Produzione\n");
    }

    pc->buffer = valore;
    pc->buffer_occupato = 1;
    pc->buffer_libero = 0;

    printf("Produzione [%d]\n", valore);

    signal_condition(&(pc->m), VARCOND_CONSUMATORI);
    leave_monitor(&(pc->m));
    printf("Uscita monitor - Produzione\n");
}

int consuma(struct prodcons *pc){

    int valore;

    enter_monitor(&(pc->m));
    printf("Ingresso monitor - Consumazione\n");

    if(pc->buffer_libero == 1){

        printf("Sospensione - Consumazione\n");
        wait_condition(&(pc->m), VARCOND_CONSUMATORI);
        printf("Riattiazione - Consumazione\n");
                
    }

    valore = pc->buffer;
    pc->buffer_occupato = 0;
    pc->buffer_libero = 1;

    printf("Consumazione [%d]\n", valore);

    signal_condition(&(pc->m), VARCOND_PRODUTTORI);
    leave_monitor(&(pc->m));
    printf("Uscita monitor - Consumazione\n");

    return valore;
}