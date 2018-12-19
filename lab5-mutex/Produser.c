#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <time.h>

void time_now();
pthread_mutex_t mutex;
char * time_spam;

void* producer(void *args){
	char * time_spam;
	int shm_id;
	shm_id = (shmget(2002,32,IPC_CREAT | 0666));

	if(shm_id == -1){
		printf("CAnt create memory\n");
		exit(0);
	}

	if((time_spam = shmat(shm_id,time_spam,0))==(char*)-1){
		printf("Warning\n");
		exit(0);
		}
}


void time_now(){
	time_t timer;
	struct tm timeval;
	while(1){
		if(!pthread_mutex_lock(&mutex)){
			timer = time(0);
			timeval = *localtime(&timer);
			sprintf(time_spam,"%.2d:%.2d:%.2d",timeval.tm_hour,timeval.tm_min,timeval.tm_sec);
			sleep(1);
			pthread_mutex_unlock(&mutex);
		}
	}
}


int main(){
	pthread_t thread;
	pthread_mutex_init(&mutex,NULL);
	char * time_spam;
	int shm_id;
	shm_id = (shmget(2002,32,IPC_CREAT|0666));
	if(shm_id == -1){
		printf("Warning\n");
		exit(0);
	}
	if((time_spam = shmat(shm_id,NULL,0)) == (char*)-1){
	printf("Error\n");
	exit(0);
	}
	while(1){
		pthread_mutex_lock(&mutex);
		printf("%s\n",time_spam);
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}

	pthread_mutex_destroy(&mutex);
	return 0;
}