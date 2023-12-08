#ifndef __PROCEDURE_H
#define __PROCEDURE_H

#include "monitor_signal_continue.h"

#define DIM 4

#define LIBERO 0
#define INUSO 1
#define OCCUPATO1 2
#define OCCUPATO2 3

#define CV_PROD1 0
#define CV_PROD2 1
#define CV_CONS1 2
#define CV_CONS2 3

typedef struct{

	int vettore[DIM];
	int stato[DIM];

	int num_liberi;
	int num_occupati_tipo1;
	int num_occupati_tipo2;

	Monitor m;
    
} MonitorPC;

void inizializza(MonitorPC * m);
void rimuovi(MonitorPC * m);
void produci_tipo_1(MonitorPC * m, int valore);
void produci_tipo_2(MonitorPC * m, int valore);
void consuma_tipo_1(MonitorPC * m, int * valore);
void consuma_tipo_2(MonitorPC * m, int * valore);

#endif
