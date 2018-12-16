#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#define FIFO "./file"
#define BUFFER_SIZE 8


void time_now(char *);

int main(int argc,char * argv[]){
	pid_t pid;
	char * buffer = (char *)calloc(BUFFER_SIZE,sizeof(char));
	mkfifo(FIFO,0777);
	pid = fork();
	if (pid == 0){
		int fd = open(FIFO,O_WRONLY);
		time_now(buffer);
		write(fd,buffer,BUFFER_SIZE);
		close(fd);
	}
	else {
		int fd = open(FIFO,O_RDONLY);
		read(fd,buffer,BUFFER_SIZE);
		printf("From proc: %s\n",buffer);
		close(fd);
		}
}


void time_now(char * str){
	time_t timer = time(0);
	struct tm timeval = *localtime(&timer);
	sprintf(str, "[%.2d:%.2d:%.2d]\n", timeval.tm_hour, timeval.tm_min, timeval.tm_sec);
}