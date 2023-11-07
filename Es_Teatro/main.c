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
    
    key_t key_shm, key_sem;
    key_shm = IPC_PRIVATE;
    key_sem = IPC_PRIVATE;
    int id_shm, id_sem;

    posto* p;

    id_shm=shmget(key_shm, sizeof(posto)*POSTI+sizeof(int), IPC_CREAT|0664);
    if(id_shm<0){
        perror("Errore nella shm\n");
        exit(1);
    }

    p=(posto*)shmat(id_shm,0,0);
    int* disp;

    if(p==((void*)-1)) {
        disp=(int*)shmat(id_shm,0,0);
        perror("errore nella shmat\n");
        exit(1);
    }
    disp=(int*)(p+POSTI);

    id_sem=semget(key_sem,1,IPC_CREAT|0664);
    if(id_sem<0){
        perror("Errore nella semget\n");
        exit(1);
    }
    semctl(id_sem,MUTEX,SETVAL,1);
    for(int i=0;i<POSTI;i++){
        p[i].stato=LIBERO;
        p[i].id_cliente=0;
    }
    (*disp)=POSTI;

    for(int i=0; i<CLIENTI; i++){
        pid_t pid;
        srand(getpid()*time(NULL));
        int sleeptime = rand()%5+1;
        sleep(sleeptime);
        consumatore(p, id_sem);
        pid=fork();
        if(pid<0){
            perror("errore nella fork\n");
            exit(1);
        }else if(pid==0){
            int num=rand()%4+1;
            (*disp)=((*disp)-num);
            printf("disponibilità: %d\n",*disp);
            if(*disp>=0){
                produttore(p, id_sem, getpid(), num, disp);
            }else{
                printf("Fine disponibilità\n");
            }
            exit(0);
        }
    }

    shmdt(disp);
    semctl(id_sem, IPC_RMID,0);
    shmctl(id_shm, IPC_RMID,0);

    return 0;
}