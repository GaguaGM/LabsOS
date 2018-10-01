#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
	 pid_t pid;
	  pid = fork();
	   if (pid > 0 ){
		            printf("Child.proc!\n");
			             printf("Pid-%d\n",getpid());
				             }
	    if (pid==0){
		             printf("Parent.proc!\n");
			              printf("Pid-%d\n",getpid());
				              }
	            return 0;
}

