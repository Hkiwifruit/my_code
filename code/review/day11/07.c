#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;

int ticket = 100;

void fun(void *arg)
{
	printf("fun\n");
	pthread_mutex_unlock(&mutex);
}

void *route(void *arg)
{
	while(1){
		pthread_cleanup_push(fun, NULL);
		pthread_mutex_lock(&mutex);
		if(ticket > 0){
			usleep(10000);
			printf("%s, sell %d\n", (char*)arg, ticket);
			ticket--;
		}else{
			pthread_exit(NULL);
			//break;
		}
		//pthread_mutex_unlock(&mutex);
		pthread_cleanup_pop(0);
	}
	printf("%s thread exit\n", (char*)arg);
}

int main()
{
	pthread_t tid1, tid2, tid3, tid4;
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&tid1, NULL, route, (void*)"thread1");
	pthread_create(&tid2, NULL, route, (void*)"thread2");
	pthread_create(&tid3, NULL, route, (void*)"thread3");
	pthread_create(&tid4, NULL, route, (void*)"thread4");

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);
	pthread_join(tid4, NULL);
	pthread_mutex_destroy(&mutex);
}
