#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>

#include "procedure.h"
#include "semafori.h"

// Funzione del PRODUTTORE
void produttore(int * p, int ds_sem) {
	// Diminuisco il semaforo SPA_DISP di 1
	// cosi da non permettere ad altri produttori di
	// produrre su questa risorsa
	Wait_Sem(ds_sem, SPAZIO_DISPONIBILE);
	// sleep() attende 2 secondi in questo caso e poi riparte
	// da dove si è fermata
	sleep(2);
	// produco sulla risorsa condivisa che in questo caso è *p
	*p = rand() % 100;
	printf("Il valore prodotto = %d\n", *p);

	// Aumento il semaforo MES_DISP di 1
	// cosi nel caso venga chiamato il consumatore 
	// potrà accedere alla risorsa condivisa
	Signal_Sem(ds_sem, MESSAGGIO_DISPONIBILE);
}

// Funzione del CONSUMATORE
void consumatore(int * p, int ds_sem) {
	// Se il valore di MES_DISP è 1 allora lo decremento a 0
	// ed entro nella sezione critica
	Wait_Sem(ds_sem, MESSAGGIO_DISPONIBILE);

	sleep(2);
	// consumo il valore della risorsa condivisa
	printf("Il valore consumato = %d\n", *p);
	// Aumento il valore di SPA_DISP cosi da avvertire
	// che è possibile scrivere sulla risorsa nuovamente
	Signal_Sem(ds_sem, SPAZIO_DISPONIBILE);
}
