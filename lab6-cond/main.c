#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/shm.h>
#include <sys/types.h>

#define MAX 10
#define MEMORY 32

int counter = 0;
char * addr;

void time_spam();
pthread_mutex_t mutex;
pthread_cond_t condition;
void * producer();
void * consumer();


void * producer(){
	while(1){
		pthread_mutex_lock(&mutex);
		time_spam();
		sleep(1);
		pthread_cond_broadcast(&condition);
		sleep(1);
		pthread_mutex_unlock(&mutex);
	}
}


void * consumer(){
	while(1){
		pthread_mutex_lock(&mutex);
			pthread_cond_wait(&condition,&mutex);
			printf("Stop %s\n",addr);
		}
		pthread_mutex_unlock(&mutex);
	}


int main(){
	void * producer();
	void * consumer();
	pthread_t thread;
	pthread_t consume;
	
	int shm_id;
	key_t semkey = ftok("main.c", 'a'); 
	if (shm_id = (shmget(semkey, MEMORY*sizeof(char), IPC_CREAT | 0666)) == -1){
	printf("Warning\n"); 
	perror(0);
	exit(0);
	} 
	addr = shmat(shm_id, NULL, 0);
	if (addr == (char*) -1) {
	perror(0);
	exit(0);
	}
	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&condition,NULL);
	pthread_create(&thread,NULL,producer,NULL);
	pthread_create(&consume,NULL,consumer,NULL);
	sleep(15);
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&condition);
}

void time_spam(){
	time_t timer;
	struct tm timeval;
	timer = time(0);
	timeval = *localtime(&timer);
	sprintf(addr,"%.2d:%.2d:%.2d",timeval.tm_hour,timeval.tm_min,timeval.tm_sec);
	sleep(1);
}
