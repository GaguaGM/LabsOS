#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/shm.h>
#include <sys/types.h>

#define MAX 10
#define MEMORY 11

int counter = 0;
char * addr;

pthread_mutex_t mutex;
pthread_cond_t condition;
void * producer();
void * consumer();

void * producer(){
	while(1){
		pthread_mutex_lock(&mutex);
		addr[counter] = 'T';
		counter++;
		if (counter == 1)
			printf("%d - %s\n",counter,addr);
		if (counter > MAX){
			pthread_cond_broadcast(&condition);
			sleep(0.5);
		} 
		pthread_mutex_unlock(&mutex);
	}
}


void * consumer(){
	while(1){
		pthread_mutex_lock(&mutex);
		while(counter < MAX){
			printf("heell\n");
			pthread_cond_wait(&condition,&mutex);
		}
		while(counter){
			addr[counter] = ' ';
			counter--;
			printf("gef",addr);
		}
		pthread_mutex_unlock(&mutex);
	}

}


int main(){
	void * producer();
	void * consumer();
	pthread_t thread;
	pthread_t consume;
	
	int shm_id;
	shm_id = ((shmget(2002,MEMORY,IPC_CREAT|0666)) == -1);
	if(shm_id == -1){
		printf("Warning\n");
		exit(0);
	}
	if((addr = shmat(shm_id,addr,0)) == (char *)-1){
	printf("Error\n");
	exit(0);
	}
	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&condition,NULL);
	pthread_create(&thread,NULL,producer,NULL);
	pthread_create(&consume,NULL,consumer,NULL);
	sleep(0.5);
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&condition);


}





