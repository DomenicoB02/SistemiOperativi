#include "buffer.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/wait.h>

int main(){

    printf("[%d] Creazione coda dei lettori\n", getpid());

    key_t chiave_queue = ftok(".",'q');
    int queue = msgget(chiave_queue, IPC_CREAT|0664);

    printf("[%d] Creazione shared memory\n", getpid());

    key_t chiave_shm = ftok(".",'m');
    int shm_id = shmget(chiave_shm, sizeof(buffer), IPC_CREAT|0644);
    if(shm_id<0){
        perror("Errore creazione shared memory");
        exit(1);
    }

    buffer *b= shmat(shm_id,NULL, 0);

    if(b == (void*)-1){
        perror("Errore attach shared memory");
        exit(1);
    }

    b->char_1 = '\0';
    b->char_2 = '\0';
    b->num_lettori = 0;
    b->num_scrittori = 0;

    printf("[%d] Creazione semafori\n", getpid());

    key_t sem_chiave = ftok(".", 's');

    int sem_id = semget(sem_chiave, 4, IPC_CREAT|0644);
    if(sem_id<0){
        perror("Errore creazione semafori");
        exit(1);
    }

    // Creazione semafori per la sincronizzazione tra lettori e scrittori
    int ret = semctl(sem_id, MUTEXL, SETVAL, 1);
    if(ret<0){
        perror("Errore inizializzazione semaforo MUTEXL");
        exit(1);
    }

    ret = semctl(sem_id, MUTEXS, SETVAL, 1);
    if(ret<0){
        perror("Errore inizializzazione semaforo MUTEXS");
        exit(1);
    }

    ret = semctl(sem_id, MUTEX, SETVAL,1);
    if(ret<0){
        perror("Errore inizializzazione semaforo MUTEX");
        exit(1);
    }

    ret = semctl(sem_id, SYNCH, SETVAL,1);
    if(ret<0){
        perror("Errore inizializzazione semaforo SYNCH");
        exit(1);
    }

    printf("[%d] Creazione semafori corretta!\n",getpid());

    for(int i=0; i<NUM_SCRITTORI; i++){
        printf("[%d] Creazione processo scrittore #%d\n", getpid(), i);
        pid_t pid = fork();
        if(pid==0){
            execl("./scrittore",NULL);

            perror("Errore exec scrittore");
            exit(1);
        }
    }

    for(int i=0; i<NUM_LETTORI; i++){
        printf("[%d] Creazione processo lettore #%d\n", getpid(), i);
        pid_t pid = fork();
        if(pid==0){
            execl("./lettore", NULL);
            perror("Errore exec lettori");
            exit(1);
        }
    }

    // il processo padre resta in attesa dei messaggi da parte dei processi lettori

    Messaggio m;
    for(int i=0; i<NUM_LETTORI+NUMERO_LETTURE; i++){
        ret=msgrcv(queue, (void*)&m, sizeof(Messaggio)-sizeof(long), MESSAGGIO,0);
        if(ret){
            printf("MESSAGGIO RICEVUTO #%d. Tipo: %ld; char_1: %c; char_2: %c\n", i, m.tipo, m.char_1, m.char_2);         
        }else{
            printf("Errore in ricezione\n");
        }
    }

    printf("[%d] In attesa di terminazione dei processi\n", getpid());
    for(int i=0; i<NUM_LETTORI+NUM_SCRITTORI; i++){
        wait(NULL);
    }

    printf("[%d] Deallocazione risorse\n", getpid());

    shmctl(shm_id, IPC_RMID, NULL);
    semctl(sem_id, 0, IPC_RMID);
    msgctl(queue, IPC_RMID, 0);


}