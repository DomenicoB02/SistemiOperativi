#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>

#include "semafori.h"
#include "procedure.h"

int main() {
	srand(time(NULL));
// Creazione di una chiave 
	key_t chiave = IPC_PRIVATE;
// Creazione di una shm attraverso l'utilizzo di shmget di dimensione di un intero
	int ds_shm = shmget(chiave, sizeof(int), IPC_CREAT|0664);
// Controllo della corretta creazione di una shm
	if(ds_shm<0){
		perror("SHM errore"); 
		exit(1); 
	}
// Creazione ed inizializzazione della risorsa condivisa *p
	int *p;
	p = (int *) shmat(ds_shm, NULL, 0); // attach alla shm di *p

// Creazione di un altra chiave
	key_t chiavesem = IPC_PRIVATE;
// Creazione di uno spazio per 2 semafori [appunto SPAZIO_DISP e MESS_DISP]
	int ds_sem = semget(chiavesem, 2, IPC_CREAT|0664);
// Controllo della corretta creazione dei due semafori
	if(ds_sem<0){
		perror("SEM errore"); 
		exit(1); 
	}

	*p=0;	// inizializzazione della risorsa condivisa

// SEMAFORI COOPERAZIONE tra 1 prod e 1 cons: NO COMPETIZIONE
// Inizializzazione dei semafori	
	semctl(ds_sem, SPAZIO_DISPONIBILE, SETVAL, 1); // ad 1
	semctl(ds_sem, MESSAGGIO_DISPONIBILE, SETVAL, 0); // a 0

// Creiamo due processi con la fork
	int pid = fork();
// il pid == 0 indicherà il figlio
	if(pid==0) {
		//figlio consumatore
		printf("Inizio figlio consumatore\n");
		consumatore(p, ds_sem);	// richiamo il consumatore
		exit(1);
	}

// rifacciola fork per il produttore
	pid = fork();
	if(pid==0) {
		//figlio produttore
		printf("Inizio figlio produttore\n");
		produttore(p, ds_sem);	// richiamo il produttore
		exit(1);
	}

//	Utilizziamo due wait() per la terminazione in quanto abbiamo 2 figli 
	wait(NULL);
	printf("primo figlio terminato\n");

	wait(NULL);
	printf("secondo figlio terminato\n");
// Deallocazione dei semafori e delle shm
    shmctl(ds_shm, IPC_RMID, NULL);
    semctl(ds_sem, 0, IPC_RMID);
        
    return 0;
}
