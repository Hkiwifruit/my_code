#include<stdio.h>
#include<pthread.h>
#include <semaphore.h>

#define SIZE 32

int RingBuf[SIZE]={0};
int step=0;
sem_t semblank;
sem_t semdata;


void *product()
{
	int i=0;
	while(1){
			sem_wait(&semblank);
			RingBuf[step++]=i;
			sem_post(&semdata);
			printf("product done! %d\n", i++);
			step%=32;
		}
	
}

void *consume()
{
	int i=0;
	while(1){
			sem_wait(&semdata);
			printf("consume done !%d\n", RingBuf[step]);
			sem_post(&semblank);	
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
	pthread_t c, p;
		sem_init(&semblank, 0, SIZE);
		sem_init(&semdata, 0, 0);

		pthread_create(&c, NULL, consume, NULL);
		pthread_create(&p, NULL, product, NULL);

		pthread_join(c, NULL);
		pthread_join(p, NULL);
		Destory();
		return 0;
	}
