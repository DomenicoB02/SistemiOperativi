#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <string.h>

int main(){
// Creazione di una shm_key per stringhe, in tal caso si usa ftok()
	key_t shm_key = ftok(".",'k');
// Creazione della shm attraverso shmget con dimensione 100
	int ds_shm = shmget(shm_key, 100, IPC_CREAT | IPC_EXCL | 0664);
// Creazione di un puntatore alla variabile p
	char * p;
// Controllo sulla creazione
	if(ds_shm < 0){
		// la risorsa già esiste (ma occorre una seconda shmget)
		ds_shm = shmget(shm_key, 100,0664);
		p = (char*) shmat(ds_shm, NULL, 0);
	}else{
		// la risorsa è stata appena creata, viene fatto l'attach alla 
		// shm di p
		p = (char*) shmat(ds_shm, NULL, 0);
		strncpy(p, "HELLO WORLD",sizeof("HELLO WORLD")); // inizializza
	}
	
	printf("Dettagli shared memory creata:\n");
	printf("...chiave IPC shm: %d\n", shm_key);
	printf("...descrittore shm: %d\n", ds_shm);
	printf("...indirizzo dopo attach: %p\n",p);
	
	printf("Contenuto SHM: %s\n",p);
// deallocazione delle risorse shm	
	shmctl(ds_shm, IPC_RMID, NULL);
	
	return 0;
}
