#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_cond_t cond;
pthread_mutex_t mutex;

void* r1(void *arg)
{
	while(1){
		pthread_cond_wait(&cond, &mutex);//等待条件
		printf("active\n");
	}
}

void* r2(void *arg)
{
	while(1){
		pthread_cond_signal(&cond);
		sleep(1);
	}
}

int main()
{
	pthread_cond_init(&cond, NULL);
	pthread_mutex_init(&mutex, NULL);
	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, r1, NULL);
	pthread_create(&tid2, NULL, r2, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
}
