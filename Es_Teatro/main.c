#include "semafori.h"
#include "procedure.h"

#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <wait.h>

int main(){
    key_t key_shm, key_sem;
    key_shm = IPC_PRIVATE;
    key_sem = IPC_PRIVATE;

    int id_sem=semget(key_sem,4,IPC_CREAT|0664);
    if(id_sem<0){
        perror("Errore con la creazione del semaforo\n");
        exit(1);
    }
//
    semctl(id_sem,SPAZIO_DISPONIBILE,SETVAL,POSTI);
    semctl(id_sem, MESSAGGIO_DISPONIBILE, SETVAL, 0);

    semctl(id_sem,MUTEX_C,SETVAL,1);
    semctl(id_sem,MUTEX_P,SETVAL,1);
//

    int id_shm=shmget(key_shm,sizeof(struct prodcons),IPC_CREAT|0664);
    if(id_shm<0){
        perror("Errore nella creazione della shared memory");
        exit(1);
    }
    
    struct prodcons *p;
    p=(struct prodcons*) shmat(id_shm,NULL,0);



    for(int i=0; i<CLIENTI; i++){
        pid_t pid;
        pid=fork();

        if(pid==0){
            printf("Processo figlio n.ro <%d>\n",i+1);
            srand(time(NULL)*getpid());
            
            produttore(p,id_sem);
            
            consumatore(p,id_sem);
            exit(1);
        }
    }
//

    
    for(int i=0;i<CLIENTI;i++){
        wait(NULL);
        printf("Processo figlio terminato\n");
    }

    //visualizza(p);

    semctl(id_sem, IPC_RMID,0);
    shmctl(id_shm, IPC_RMID,0);

    return 0;
}
