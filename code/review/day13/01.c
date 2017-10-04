#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define BUF_SZ 5
#define	PRO_CNT 1
#define CUS_CNT 1

sem_t full;
sem_t empty;
pthread_mutex_t mutex;
int buf[BUF_SZ];
int widx = 0;
int ridx = 0;

pthread_t threads[PRO_CNT+CUS_CNT];

void* pro(void* arg)
{
	int num = 0;
	int i;
	while(1){
		sem_wait(&full);
		pthread_mutex_lock(&mutex);

		for(i=0; i<BUF_SZ; i++){
			printf("%02d", i);
			if(buf[i] == -1)
				printf("null");
			else
				printf("%d", buf[i]);
			if(i == widx)
				printf("-----");
			printf("\n");
		}
		buf[widx] = num++;
		widx = (widx+1)%BUF_SZ;

		pthread_mutex_unlock(&mutex);
		sem_post(&empty);

	}
}

void* cus(void* arg)
{
	int i;
	while(1){
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
		for(i=0; i<BUF_SZ; i++){
			printf("%02d", i);
			if(buf[i] == -1)
				printf("null");
			else
				printf("%d", buf[i]);
			if(i == widx)
				printf("-----");
			printf("\n");
		}
		buf[ridx];
		ridx = (ridx+1)%BUF_SZ;
		pthread_mutex_unlock(&mutex);
		sem_post(&full);
	}
}

int main(void)
{
	sem_init(&full, 0, BUF_SZ);
	sem_init(&empty, 0, 0);
	pthread_mutex_init(&mutex, NULL);

	int i =0 ;
	for(;i<PRO_CNT; i++){
		int *p = (int*)malloc(sizeof(int));
		*p = i;
		pthread_create(&threads[i], NULL, pro, (void*)p);
	}
	for(i=0; i<CUS_CNT; i++){
		int *p = (int*)malloc(sizeof(int));
		*p = i;
		pthread_create(&threads[i], NULL, cus, (void*)p);
	}
	for(i=0; i<PRO_CNT+CUS_CNT; i++){
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_destroy(mutex);
	sem_destroy(&empty);
	sem_destroy(&full);
}
