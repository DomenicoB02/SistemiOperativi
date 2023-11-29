#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/msg.h>

#include "header_msg.h"

int main() {

        /* TBD: Creare le code di messaggi */
        /* TBD */
        int id_queue_collettore_1 = msgget(IPC_PRIVATE,IPC_CREAT|0664);
        /* TBD */
        int id_queue_collettore_2 = msgget(IPC_PRIVATE, IPC_CREAT|0664);
        /* TBD */
        int id_queue_server = msgget(IPC_PRIVATE, IPC_CREAT|0664);

        pid_t pid;
        /* TBD: Creare il processo figlio Server, 
                passandogli lo id della coda */


        pid=fork();
        if(pid==0){
                server(id_queue_server);
                exit(0);
        }

        /* TBD: Creare il primo processo figlio Collettore, 
                passandogli lo "id_collettore",
                lo id della coda per ricevere dai sensori,
                e lo id della coda per inviare al server
        */
        int id_collettore_1 = 1;
        pid=fork();
        if(pid==0){
                collettore(id_collettore_1,id_queue_collettore_1,id_queue_server);
                exit(0);
        }
        
        /* TBD: Creare il secondo processo figlio Collettore, 
                passandogli lo "id_collettore",
                lo id della coda per ricevere dai sensori,
                e lo id della coda per inviare al server
        */ 
        int id_collettore_2 = 2;
        pid=fork();
        if(pid==0){
                collettore(id_collettore_2,id_queue_collettore_2,id_queue_server);
                exit(0);
        }

        for(int i=0; i<NUM_SENSORI_PER_COLLETTORE; i++) {

                int id_sensore = i+1;

                /* TBD: Creare i processi figli Sensore, 
                        passandogli lo "id_sensore",
                        e lo id della coda per inviare al primo collettore
                */
                pid=fork();
                sensore(id_sensore,id_queue_collettore_1);
                exit(0);
        }


        for(int i=0; i<NUM_SENSORI_PER_COLLETTORE; i++) {

                int id_sensore = i+1;

                /* TBD: Creare i processi figli Sensore, 
                        passandogli lo "id_sensore",
                        e lo id della coda per inviare al secondo collettore
                */
                pid = fork();
                if(pid==0){
                        sensore(id_sensore,id_queue_collettore_2);
                        exit(0);
                }
        }

        /* TBD: Attendere la terminazione di tutti i processi figli */
        for(int i=0;i<NUM_COLLETTORI+NUM_MESSAGGI_PER_SENSORE+NUM_SENSORI_PER_COLLETTORE;i++){
                wait(NULL);
        }

        /* TBD: De-allocare le code di messaggi */
        msgctl(id_queue_collettore_1,IPC_RMID,0);
        msgctl(id_queue_collettore_2,IPC_RMID,0);
        msgctl(id_queue_server,IPC_RMID,0);
        
        return 0;
}