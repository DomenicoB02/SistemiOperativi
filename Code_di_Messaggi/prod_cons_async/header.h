#ifndef _HEADER_H_
#define _HEADER_H_

#define MESSAGGIO 1

typedef char msg[40];

typedef struct{
    long tipo;
    msg mess;
}Messaggio;

void Produttore(int queue, char* m);
void Consumatore(int queue);
void printMsgInfo(int queue);

#endif // _HEADER_H_