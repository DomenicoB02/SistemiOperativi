#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
	int pid,st;
	pid=fork();
	
	if(pid==-1){
		perror("fork fallita");
		return -1;
	}
	else if(pid==0){
	
		char** flags=(char**) malloc(sizeof(char*)*argc);
		
		for(int i=0;i<argc-2;i++){
			*(flags+i) = (char*)malloc(sizeof(char)* strlen(argv[i+2]));
			strcpy(*(flags+i),argv[i+2]);
			printf("Parametro %d: %s\n", i+2, *(flags+i));
		}
		execvp(argv[1],flags);
		
		for(int i=0;i<argc-2;i++){
			free(*(flags+i));
		}
		free(flags);
		
		printf("Zona Vietata\n");
		kill(getppid(),SIGKILL);
		exit(1);
		
	}else if(pid>0){
		printf("Processo padre, con PID %d\n",getpid());
		
		wait(NULL);
		
		printf("Chiamata di %s effettuata con successo!\n", argv[1]);
		printf("Il processo padre termina\n");
		exit(0);
	}
	return 0;
	

}
