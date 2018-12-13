#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#define FIFO "./file"
#define BUFFER_SIZE 8
char* ctime (const time_t * timer);

int main(){
	pid_t pid;
	char * buffer = (char *)calloc(BUFFER_SIZE,sizeof(char));
	mkfifo(FIFO,0777);
	pid = fork();
	if (pid == 0){
		printf("CHILD:HIIIIIII\n");
		int fd = open(FIFO,O_WRONLY);
		time_t data = time(0);
		time (&data);
		sprintf(buffer,"%s",ctime(&data));
		write(fd,buffer,BUFFER_SIZE);
		close(fd);
	}
	else {
		printf("PARENT:HELLOUUUU\n");
		int fd = open(FIFO,O_RDONLY);
		read(fd,buffer,BUFFER_SIZE);
		printf("From proc: %s\n",buffer);
		close(fd);
		}
}
