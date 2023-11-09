#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#define SPAZIO_DISPONIBILE 0
#define MESSAGGIO_DISPONIBILE 1
#define MUTEX_P 2
#define MUTEX_C 3

#define POSTI 10
#define CLIENTI 6

#define LIBERO 0
#define OCCUPATO 1
#define INUSO 2


typedef struct{
    int id_cliente;
    int stato;
}posto;

struct prodcons{
    posto buffer[POSTI];
    int stato_posto[POSTI];
};

void produttore(struct prodcons*, int id_sem);
void consumatore(struct prodcons*, int id_sem);
void visualizza(struct prodcons*);

#endif // _PROCEDURE_H_