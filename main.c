#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char* argv[]){
	
	key_t shm_key = ftok(".",'k');
	int shm = shmget(shm_key, 100, IPC_CREAT | IPC_EXCL | 0664);
	char * p[100];
	
	if(shm < 0){
		
		shm = shmget(shm_key, 100, 0664);
		p[0] = (char*) shmat(shm,NULL,0);
			
	}else{
			
		p[0] = (char*) shmat(shm,NULL,0);
		
	}
		
	printf("Dettagli della shared memory creata:\n");
	printf("...chiave IPC shm: %d\n",shm_key);
	printf("...descrittore shm: %d\n",shm);
	
	
	key_t pid= fork();
	
	// -------------------FALLITO------------------------
	
	if(pid == -1){
	
		perror("fork fallita\n");
		return -1;
		
	}
	
	// -------------------FIGLIO------------------------
	
	else if(pid==0){
		
		p[0] = shmat(shm,NULL,0);
		// --------SCRITTURA------------
		if(strcmp(argv[1],"w")==0){
		
			printf("\nFunzione Scrittura\n");
			strcpy(p[0],argv[2]);
				
			
		}
		// --------LETTURA--------------
		else if(strcmp(argv[1],"r")==0){
		
			printf("\nFunzione Lettura\n");
			printf("%s\n",p[0]);
			
		}
		// -------ELIMINAZIONE----------
		else if(strcmp(argv[1],"d")==0){
		
			printf("\nFunzione Cancellazione\n");
			shmctl(shm, IPC_RMID, NULL);	
			
		}
		//-------IN_CASO_DI_PB---------
		else{
			printf("\nERROR\n");
		}
		
		exit(1);
		
	} 
	
	// -------------------PADRE------------------------
	
	else if(pid > 0){

		wait(NULL);
		
		printf("Ritorno alla variabile padre con PID: [%d]\n",getpid());
		exit(0);
	}
	
	return 0;
	
}
