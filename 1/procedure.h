#include "monitor_hoare.h"

struct prodcons{

    Monitor m;

    int buffer;
    
    int buffer_occupato;
    int buffer_libero

};

#define VARCOND_CONSUMATORI 0
#define VARCOND_PRODUTTORI 1

void produci(struct prodcons *, int );
int consuma(struct prodcons *);

