#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main (int argc, char * argv[]){
	pid_t pid = getpid();

	if ((pid = fork()) == 0){
		printf("Child_process %d\n", getpid());
		sleep(5);
		printf("End %d\n", getpid());
	}
	else {
		printf("Parent_process %d\n", getpid());
		sleep(1);
		printf("End %d\n", getpid()); 
}
}
