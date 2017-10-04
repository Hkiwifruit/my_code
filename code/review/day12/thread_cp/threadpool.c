#include "threadpool.h"
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <pthread.h>

void threadpool_init(threadpool_t* pool, int threads)
{
	condition_init(&pool->ready);
	pool->first = NULL;
	pool->last = NULL;
	pool->counter = 0;
	pool->idle = 0;
	pool->max_threads = threads;
	pool->quit = 0;
}

void *route(void *arg)
{
	threadpool_t *pool = (threadpool_t*)arg;
	printf("%x thread is starting\n", pthread_self());

	int timeout = 0;

	while(1){
		condition_lock(&pool->ready);
		pool->idle++;
		while(pool->first == NULL && pool->quit == 0){
			printf("%x thread is wait\n", pthread_self());
			struct timespec ts;
			clock_gettime(CLOCK_REALTIME, &ts);
			ts.tv_sec += 2;
			int t = condition_timedwait(&pool->ready, &ts);
			if(t == ETIMEDOUT){
				printf("%x thread time out\n", pthread_self());
				timeout = 1;
				break;
			}
		}
		pool->idle--;

		if(pool->first != NULL){
			task_t *p = pool->first;
			pool->first = p->next;

			condition_unlock(&pool->ready);
			p->run(p->arg);
			condition_lock(&pool->ready);

			free(p);
		}

		if(pool->quit == 1 && pool->first == NULL){
			pool->counter--;
			if(pool->counter == 0){
				condition_signal(&pool->ready);
			}
			condition_unlock(&pool->ready);
			break;
		}

		if(timeout == 1 && pool->first == NULL){
			pool->counter--;
			condition_unlock(&pool->ready);
			break;
		}
		condition_unlock(&pool->ready);
	}
	printf("%x thread exit\n", pthread_self());
}

void threadpool_add_task(threadpool_t *pool, void* (*run)(void*), void* arg)
{
	task_t *p = (task_t*)malloc(sizeof(task_t));
	memset(p, 0x00, sizeof(task_t));
	p->run = run;
	p->arg = arg;
	p->next = NULL;
	condition_lock(&pool->ready);

	if(pool->first == NULL){
		pool->first = p;
	}else{
		pool->last->next = p;
	}
	pool->last = p;

	if(pool->idle > 0){
		condition_signal(&pool->ready);
	}else if(pool->counter < pool->max_threads){
		pthread_t tid;
		pool->counter++;
		pthread_create(&tid, NULL, route, (void*)pool);
	}

	condition_unlock(&pool->ready);
}

void threadpool_destroy(threadpool_t *pool)
{
	if(pool->quit == 1)
		return ;
	condition_lock(&pool->ready);

	pool->quit = 1;
	if(pool->idle > 0)
		condition_broadcast(&pool->ready);

	while(pool->counter > 0)
		condition_wait(&pool->ready);

	condition_unlock(&pool->ready);
	condition_destroy(&pool->ready);
}

