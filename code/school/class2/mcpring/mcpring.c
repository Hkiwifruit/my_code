#include<stdio.h>
#include<pthread.h>
#include <semaphore.h>

#define SIZE 32

int RingBuf[SIZE]={0};
int step=0;
sem_t semblank;
sem_t semdata;

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;

void *product2()
{
	int i=0;
	while(1){
			pthread_mutex_lock(&lock1);
			sem_wait(&semblank);
			RingBuf[step++]=i;
			sem_post(&semdata);
			
			pthread_mutex_unlock(&lock1);
			printf("product2 done! %d\n", i++);
			step%=32;
		}
}

void *product1()
{
	int i=0;
	while(1){
		pthread_mutex_lock(&lock1);
			sem_wait(&semblank);
			RingBuf[step++]=i;
			sem_post(&semdata);
		pthread_mutex_unlock(&lock1);
			printf("product1 done! %d\n", i++);
			step%=32;
		}
	
}

void *consume1()
{
	int i=0;
	while(1){
		pthread_mutex_lock(&lock2);
			sem_wait(&semdata);
			printf("consume1 done !%d\n", RingBuf[step]);
			sem_post(&semblank);	
		pthread_mutex_unlock(&lock2);
			//sleep(2);
		}
}

void *consume2()
{
	while(1){
		pthread_mutex_lock(&lock2);
			sem_wait(&semdata);
			printf("consume2 done !%d\n", RingBuf[step]);
			sem_post(&semblank);	
		pthread_mutex_unlock(&lock2);
			sleep(1);
	}
}

void Destory()
{
	sem_destroy(&semdata);
	sem_destroy(&semblank);
	printf("destory sem success!\n");
}
int main()
{
		pthread_t c1, c2, p1, p2;
		sem_init(&semblank, 0, SIZE);
		sem_init(&semdata, 0, 0);

		pthread_create(&c1, NULL, consume1, NULL);
		pthread_create(&c2, NULL, consume2, NULL);
		pthread_create(&p1, NULL, product1, NULL);

		pthread_create(&p2, NULL, product2, NULL);
		pthread_join(c1, NULL);
		pthread_join(c2, NULL);
		pthread_join(p1, NULL);
		pthread_join(p2, NULL);
		Destory();
		return 0;
	}
