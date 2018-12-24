#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>


struct sembuf sem_lock = {0,-1,0}, sem_open = {0,1,0};
int main(){
	char * time_spam;
	key_t key = ftok("/tmp",'a');
	int shmid = (shmget(key,32,0666));
	int semid = (semget(key,1,0666));
	if (semid == -1){
		printf("error\n");
		exit(0);
	}
	if(shmid == -1){
		printf("cant open mem\n");
		exit(0);
	}
	if((time_spam = shmat(shmid,time_spam,0)) == (char*)-1)
	{
		printf("Error\n");
		exit(0);
	}


	while(1){
		semop(semid,&sem_lock,1);
		printf("%s",time_spam);
		semop(semid,&sem_open,1);
		sleep(1);
	}
	return 0;
}