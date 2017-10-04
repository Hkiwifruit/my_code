#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>


void *thread1(void *val)
{
	printf("thread1 returning...!\n");
	return (void *)1;
}

void *thread2(void *val)
{
	printf("thread2 exiting...!\n");
	pthread_exit((void *)2);
}

int main()
{
	pthread_t tid;
	void * tret;
		pthread_create(&tid, NULL, thread1, NULL);
		pthread_join(tid, &tret);
		printf("thread return-> thread_id: %u, return code: %d\n", (unsigned long)tid, (int)tret );
	
		pthread_create(&tid, NULL, thread1, NULL);
		pthread_join(tid, &tret);
		printf("thread exit-> thread_id: %u, return code: %d\n", (unsigned long)tid, (int)tret );
		return 0;
}


//void *thread_run(void *arg)
//{
//	while(1){
//		printf("fun thread, tid: %u, pid: %d\n", pthread_self(), getpid());
//		sleep(2);
//	}
//}
//
//int main()
//{
//	pthread_t id;
//	pthread_create(&id, NULL, thread_run, NULL);

//	pthread_join();
//	while(1){
//		printf("main thread, tid: %u, pid: %d\n", pthread_self(), getpid());
//		sleep(1);
//	}
//return 0;
//}
