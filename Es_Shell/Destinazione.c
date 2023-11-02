#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
	int i,pid;
	pid=fork();
	
	if(pid==-1){
		perror("Fork fallita");
		exit(1);
	}else if(pid==0){
		printf("Processo figlio, con PID %d\n", getpid());
		printf("Command line passata al main(): \n");
		printf("argv[0]: %s\n",argv[0]);
		printf("argv[1]: %s\n",argv[1]);
		int j=2;
		while(argv[j]!=NULL){
			printf("argv[%d]: %s\n",j,argv[j]);
			j++;
		}
		printf("Attendo 3 secondi\n");
		
		for(i=0;i<3;i++){
			sleep(1);
			printf(".\n");
		}
		
		execl("/bin/cp","cp",argv[1],argv[2],NULL);
		
		perror("Se arrivo in questo punto, qualcosa è andato storto...\n");
		kill(getpid(),SIGKILL);
		exit(1);
	}else{
		printf("Sono il processo padre, con pid %d\n", getpid());
		
		wait(NULL);
		
		printf("Copia effettuata con successo!\n");
		printf("Il processo padre termina\n");
		
		exit(0);
	}
	return 0;
}
