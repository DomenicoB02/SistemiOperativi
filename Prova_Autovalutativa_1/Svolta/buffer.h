#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "semafori.h"

#define NUM_LETTORI 5
#define NUM_SCRITTORI 3
#define NUMERO_LETTURE 5
#define NUMERO_SCRITTURE 5

#define MUTEXL 0
#define MUTEXS 1
#define MUTEX 2
#define SYNCH 3

#define MESSAGGIO 1

typedef struct{
    char char_1;
    char char_2;
    int num_lettori;
    int num_scrittori;
}buffer;

typedef struct{
    long tipo;
    char char_1;
    char char_2;
}Messaggio;

void leggi_buffer(  buffer *b,
                    int sem_id,
                    char *val_1,
                    char *val_2,
                    int queue);

void scrivi_buffer( buffer *b,
                    int sem_id,
                    char val_1,
                    char val_2);

#endif // _BUFFER_H_