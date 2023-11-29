#ifndef _HEADER_
#define _HEADER_

#define TOPIC1 1
#define TOPIC2 2

#define NUM_PUBLISHERS_PER_TOPIC 1
#define NUM_SUBSCRIBERS_PER_TOPIC 2

#define NUM_MESSAGGI 3
#define TOTALE_SUBSCRIBER (NUM_PUBLISHERS_PER_TOPIC * 2)
#define TOTALE_MESSAGGI (NUM_PUBLISHERS_PER_TOPIC * 2 * NUM_MESSAGGI)

typedef struct {

    /* TBD: 
        Definire la struttura del messaggio, includendo un topic (numerico) e un valore (numerico)*/
    long topic;
    int val;

} messaggio_valore;

typedef struct {

    /* TBD: 
        Definire la struttura del messaggio, includendo un topic (numerico) e lo ID della coda su cui ricevere i messaggi*/
    long topic;
    int coda_id;

} messaggio_registrazione;

#endif