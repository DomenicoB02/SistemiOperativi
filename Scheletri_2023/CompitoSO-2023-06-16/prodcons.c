#include <stdio.h>

#include "prodcons.h"


void init_monitor_buffer_singolo(MonitorBufferSingolo * b) {

    /* TBD: Inizializzare il monitor */
}

void produzione_buffer_singolo(MonitorBufferSingolo * b, int val) {

    /* TBD: Completare la produzione sul buffer singolo con sincronizzazione */

    b->buffer = val;

}

int consumazione_buffer_singolo(MonitorBufferSingolo * b) {

    /* TBD: Completare la consumazione dal buffer singolo con sincronizzazione */

    int val;

    val = b->buffer;

    return val;
}

void remove_monitor_buffer_singolo(MonitorBufferSingolo * b) {

    /* TBD: Disattivare l'oggetto monitor */
}