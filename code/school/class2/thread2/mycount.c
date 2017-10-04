#include<stdio.h>
#include<pthread.h>

int count=0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *threadCount(void *arg)
{
	int i=0;
	int tmp=0;
	while(i<5000){
		pthread_mutex_lock(&lock);
		tmp= count;
		printf("thread: %u, count is : %d\n", pthread_self(), count);
		count=tmp+1;
		pthread_mutex_unlock(&lock);
		i++;
	}
}

int main()
{
	pthread_t td1, td2;
	pthread_create(&td1, NULL, threadCount, NULL);
	pthread_create(&td2, NULL, threadCount, NULL);

	pthread_join(td1, NULL);
	pthread_join(td2, NULL);

	printf("count = %d\n", count);
	return 0;
}
