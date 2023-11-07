#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#define MUTEX 0

#define POSTI 10
#define CLIENTI 6

#define LIBERO 0
#define INUSO 1
#define OCCUPATO 2

typedef struct{
    int id_cliente;
    int stato;
}posto;

void produttore(posto*, int, int, int, int*);
void consumatore(posto*, int);

#endif // _PROCEDURE_H_