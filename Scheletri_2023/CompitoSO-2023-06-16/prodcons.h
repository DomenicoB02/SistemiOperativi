#ifndef _circolare_
#define _circolare_

#include "monitor_hoare.h"

typedef struct {

    int buffer;

    /* TBD: Introdurre ulteriori variabili per la gestione del buffer
            e per la sincronizzazione */

} MonitorBufferSingolo;


void init_monitor_buffer_singolo(MonitorBufferSingolo * b);
void produzione_buffer_singolo(MonitorBufferSingolo * b, int val);
int consumazione_buffer_singolo(MonitorBufferSingolo * b);
void remove_monitor_buffer_singolo(MonitorBufferSingolo * b);


typedef struct {

    /* TBD: Definire una struttura dati e le costanti per lo scambio di messaggi */

} messaggio;


#endif