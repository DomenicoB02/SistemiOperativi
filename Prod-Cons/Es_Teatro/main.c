#include "semafori.h"
#include "procedure.h"

#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>

int main(){
    
    // dichiariamo le chiavi per la memoria condivisa e i semafori
    key_t key_shm, key_sem;
    key_shm = IPC_PRIVATE;
    key_sem = IPC_PRIVATE;
    int id_shm, id_sem;
	
	// richiamo il puntatore alla struct presente in procedure.h
    posto* p;
	
	// creo una memoria condivisa 'id_shm' con dimensione pari al
	// secondo valore della funzione shmget.
	// Questo spazio condiviso è utilizzato per archiviare un array di struct
	// e una variabile 'int' chiamata 'disp'
    id_shm=shmget(key_shm, sizeof(posto)*POSTI+sizeof(int), IPC_CREAT|0664);
    
    // controllo della corretta esecuzione della shmget
    if(id_shm<0){
        perror("Errore nella shm\n");
        exit(1);
    }
	
	// vengono inizializzati p e disp, shmat serve a collegare un processo
	// ad un segmento di memoria condivisa.
	// In questo caso a id_shm
    p=(posto*)shmat(id_shm,0,0);
    int* disp;
	
	// controllo che p sia stata collegata correttamente
    if(p==((void*)-1)) {
        disp=(int*)shmat(id_shm,0,0);
        perror("errore nella shmat\n");
        exit(1);
    }
    
    // viene inizializzato disp come puntatore ad intero con valore p+POSTI
    disp=(int*)(p+POSTI);
	
	// viene creato un semaforo 'id_sem'...
    id_sem=semget(key_sem,1,IPC_CREAT|0664);
    // controllo dell'apertura corretta di id_sem
    if(id_sem<0){
        perror("Errore nella semget\n");
        exit(1);
    }
    // ... ed inizializzato con valore 1
    semctl(id_sem,MUTEX,SETVAL,1);
    // vengono inizializzati tutti i posti a LIBERO e tutti gli id_cliente
    // allo stesso modo
    for(int i=0;i<POSTI;i++){
        p[i].stato=LIBERO;
        p[i].id_cliente=0;
    }
   
	// il puntatore alla variabile disp viene impostato come POSTI
    (*disp)=POSTI;
    // comincia un ciclo for che verrà reiterato per il numero di CLIENTI
    // presenti in procedure,h
    for(int i=0; i<CLIENTI; i++){
    	// pid_t è un tipo di dato che indica che il valore pid che stiamo 
    	// rappresentando è un int, praticamente è la dichiarazione del pid
        pid_t pid;
        // definisco l'algoritmo di generazione casuale dei numeri
        srand(getpid()*time(NULL));
        // sleeptime e sleep, una è il range di numeri che intendo utilizzare
        // l'altra è la funzione che mi permetterà di di mandare in attesa
        // la funzione per quel tempo
        int sleeptime = rand()%5+1;
        sleep(sleeptime);
        // richiamo la funzione consumatore passandogli:
        // - la struct posto
        // - l'id del semaforo
        consumatore(p, id_sem);
        
        // utilizzo la fork per creare CLIENTI processi figli
        pid=fork();
        // semplice controllo per l'apertura dei processi figli
        if(pid<0){
            perror("errore nella fork\n");
            exit(1);
        }
        // in caso di apertura corretta del pid
        else if(pid==0){
        	// creazione di un numero randomico da 1 a 4, indica il numero
        	// di biglietti acquistati da un singolo cliente
            int num=rand()%4+1;
            // aggiornamento del numero della disponibilità dei posti rimanenti
            (*disp)=((*disp)-num);
            printf("disponibilità: %d\n",*disp);
            // se ci sono ancora posti disponibili apriamo il ciclo
            if(*disp>=0){
            	// richiamo la funzione produttore passandogli:
            	// - la struct
            	// - l'id del semaforo
            	// - il pid del processo corrente
            	// - il numero di acquisti di ogni cliente
            	// - la disponibilità residua
                produttore(p, id_sem, getpid(), num, disp);
            }else{
                printf("Fine disponibilità\n");
            }
            exit(0);
        }
    }
	
	// dealloco tutto lo spazio in memoria
    shmdt(disp);
    semctl(id_sem, IPC_RMID,0);
    shmctl(id_shm, IPC_RMID,0);

    return 0;
}
