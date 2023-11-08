#include <stdio.h>
#include <unistd.h>

int main(void){
	int pid,ppid;
	pid=getpid();
	ppid=getppid();
	printf("%d e %d",pid,ppid);
	return 0;
}
