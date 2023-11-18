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

    printf("DEBUG");


    int id_sem=semget(IPC_PRIVATE,4,IPC_CREAT|0664);
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
    int id_shm=shmget(IPC_PRIVATE,sizeof(posto),IPC_CREAT|0664);
    if(id_shm<0){
        perror("Errore nella creazione della shared memory");
        exit(1);
    }

    posto *p[POSTI];
    *p = shmat(id_shm,NULL,0);
    if(*p==(void*)-1){
        perror("Errore nell'attach del vettore di struct");
        exit(1);
    }

    int num=0;
    int disp=POSTI;
    
    for(int i=0; i<CLIENTI; i++){
        srand(getpid()*time(NULL));
        num=(rand()%4)+1;
        if(disp>=num){
        pid_t pid=fork();
            if(pid==0){
                for(int j=disp;j>(disp-num);j--){
                    consumatore(*p,id_sem,j);
                    
                    produttore(*p,id_sem,num,j);
                    exit(0);
                }
            }else if(pid<0){
                printf("Fork non creata correttamente ");
            }
        }else{
            printf("Fine disponibilità\n");
        }
        disp=disp-num;
    }
    
    visualizza(*p);

    for(int i=0;i<CLIENTI;i++){
        wait(NULL);
        exit(0);
    }

    semctl(id_sem, IPC_RMID,0);
    shmctl(id_shm, IPC_RMID,0);

    return 0;
}
