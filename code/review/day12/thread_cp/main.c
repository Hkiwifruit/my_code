#include "threadpool.h"

void* mytask(void *arg)
{
	int i = *(int*)arg;
	printf("%x thread runing on task %d\n", pthread_self(), i);
	sleep(1);
}

int main()
{
	threadpool_t pool;
	threadpool_init(&pool, 3);
	int i;
	for(i = 0; i<10; i++){
		int *p = (int*)malloc(sizeof(int));
		*p = i;
		threadpool_add_task(&pool, mytask, (void*)p);
	}

	threadpool_destroy(&pool);
}
