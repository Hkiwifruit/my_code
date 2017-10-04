#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *route(void* arg)
{
	int i = 0;
	while(1){
		if(i++ == 10)
		printf("I am thread one\n");
	}
	pthread_exit(NULL);//线程自行终止
}

int main(void)
{
	pthread_t tid;
	pthread_create(&tid, NULL, route, NULL);

	//for(;;){
	//	printf("I am main thread\n");
	//}

	//sleep(5);
	//pthread_cancel(tid);//他杀
	pthread_join(tid, NULL);//主线程等待副线程执行完
}
