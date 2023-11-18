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

#define DIM 3

typedef struct{
    int id_cliente;
    int stato[DIM];
}posto;

void produttore(posto*, int id_sem, int num,int j);
void consumatore(posto*, int id_sem,int j);
void visualizza(posto*);

#endif // _PROCEDURE_H_