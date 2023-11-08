#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	int N=3, i, pid;
	for(i=0; i<N; i++){
		pid=fork();
		if(pid==0){
			printf("Sono il processo figlio, cone PID: %d\n",getpid());
			i=3;
		}
	}
	return 0;
}
