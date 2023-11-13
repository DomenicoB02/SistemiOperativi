#ifndef _SEMAFORI_H_
#define _SEMAFORI_H_

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int Wait_Sem(int sem_id, int numsem);
int Signal_Sem(int sem_id, int numsem);

#endif // _SEMAFORI_H_