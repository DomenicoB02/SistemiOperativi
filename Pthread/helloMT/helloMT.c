#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5

void *PrintHello(void *threadid){
    printf("\n%ld: Hello World!\n",(long)threadid);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    pthread_t threads[NUM_THREADS];
    int rc, t;

    for(t=0;t<NUM_THREADS;t++){
        printf("Creating thread %d\n",t);

        // creazione
        rc=pthread_create(&threads[t],NULL,PrintHello,(void*)t);
        if(rc){
            printf("Errore; return code from pthread_create() is %d\n",rc);
            exit(1);
        }
    }
    pthread_exit(NULL);
}