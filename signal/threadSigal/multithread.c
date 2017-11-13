/*************************************************************************
	> File Name: multithread.c
	> Author: 
	> Mail: 
	> Created Time: Tue Nov  7 15:47:35 2017
 ************************************************************************/

#include<stdio.h>
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

pthread_mutex_t work_mutex;
pthread_cond_t work_cond;
int count = 0;
int flag = 0;

void *myprint(void* arg) {

    pthread_mutex_lock(&work_mutex);
	while(1) {
		for(int i=0;i<5;i++){
			printf("i am son\n");
		}
		pthread_cond_signal(&work_cond);
		pthread_cond_wait(&work_cond,&work_mutex);
		
	}
	pthread_mutex_unlock(&work_mutex);
}

int main(void) {

	pthread_t a_thread;
	pthread_mutex_init(&work_mutex,NULL);
	pthread_cond_init(&work_cond,NULL);
	pthread_mutex_lock(&work_mutex);
	pthread_create(&a_thread,NULL,myprint,NULL);
	while(1) {
		if(count==3) {
			return 0;
		}
		count++;
		pthread_cond_wait(&work_cond,&work_mutex);
		for(int i=0;i<10;i++) {
			printf("i am father\n");
		}
		pthread_cond_signal(&work_cond);
	}
	pthread_mutex_unlock(&work_mutex);
	return 0;
}
