#include "buffer.h"

#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

void send_values(char *char_1, char *char_2, int queue){

    Messaggio m;

    // costruzione del messaggio da trasmettere
    m.tipo = MESSAGGIO;
    m.char_1 = *char_1;
    m.char_2 = *char_2;

    // invio messaggio

    msgsnd(queue, (void*)&m, sizeof(Messaggio)-sizeof(long), 0);

    printf("[%d] MESSAGGIO INVIATO.\nTipo: %ld; char_1: %c; char_2: %c\n",
            getpid(), m.tipo, m.char_1, m.char_2);

}

void leggi_buffer(buffer *b, int sem_id, char *char_1, char *char_2 , int queue){

    // Inizio Lettura
    
    Wait_Sem(sem_id, MUTEXL);

    b->num_lettori++;
    if(b->num_lettori == 1){
        Wait_Sem(sem_id, SYNCH);
    }

    Signal_Sem(sem_id, MUTEXL);

    printf("[%d] Lettura buffer: char_1 = %c, char_2 = %c\n",
            getpid(), b->char_1 , b->char_2);

    sleep(1);

    // Lettura dei caratteri e conversione 
    *char_1 = b->char_1 +32;
    *char_2 = b->char_2 -32;

    send_values(char_1, char_2, queue);

    // Fine lettura

    Wait_Sem(sem_id, MUTEXL);

    b->num_lettori--;
    if(b->num_lettori == 0){
        Signal_Sem(sem_id, SYNCH);
    }

    Signal_Sem(sem_id, MUTEXL);

}

void scrivi_buffer(buffer *b, int sem_id, char char_1, char char_2){

    // Inizio scrittura
    Wait_Sem(sem_id, MUTEXS);

    b->num_scrittori = b->num_scrittori +1;
    if(b->num_scrittori == 1){
        Wait_Sem(sem_id, SYNCH);
    }

    Signal_Sem(sem_id, MUTEXS);
    Wait_Sem(sem_id, MUTEX);

    printf("[%d] Scrittura buffer: char_1 = %c, char_2 = %c\n",
            getpid(), char_1, char_2);

    // Scrittura dei caratteri
    b->char_1 = char_1;
    b->char_2 = char_2;

    // Fine scrittura

    Signal_Sem(sem_id, MUTEX);
    Wait_Sem(sem_id, MUTEXS);

    b->num_scrittori = b->num_scrittori -1;

    if(b->num_scrittori == 0){
        Signal_Sem(sem_id, SYNCH);
    }

    sleep(1);

    Signal_Sem(sem_id, MUTEXS);

}