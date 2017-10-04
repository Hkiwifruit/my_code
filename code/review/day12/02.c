#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define CONSUMER_COUNT 2
#define	PRODUCER_COUNT 2

typedef struct node_{
	struct node_ *next;
	int num;
} node_t;

node_t *head = NULL;
pthread_t thread[CONSUMER_COUNT+PRODUCER_COUNT];
pthread_cond_t cond;
pthread_mutex_t mutex;

void* consume(void* arg)
{
	int id = *(int*)arg;
	srand(getpid());
	while(1){
		pthread_mutex_lock(&mutex);

		while(head == NULL){
			printf("%d consume wait\n", id);
			pthread_cond_wait(&cond, &mutex);
		}
		printf("wait end!\n");
		node_t *p = head;
		head = head->next;
		printf("%x thread consume %d\n", id, p->num);
		pthread_mutex_unlock(&mutex);
	}
}

void* produce(void* arg)
{
	int i = 0;
	int id = *(int*)arg;
	srand(getpid());
	while(1){
		pthread_mutex_lock(&mutex);

		node_t *p = (node_t*)malloc(sizeof(node_t));
		memset(p, 0x00, sizeof(node_t));
		p->num = i++;
		if(head == NULL){
			head = p;
		}else{
			p->next = head;
			head = p;
		}
			
		printf("%d produce\n", id);
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
}

int main()
{
	int i = 0;
	pthread_cond_init(&cond, NULL);
	pthread_mutex_init(&mutex, NULL);
	for(; i<CONSUMER_COUNT; i++){
		int *p = (int*)malloc(sizeof(int));
		*p = i;
		pthread_create(&thread[i], NULL, consume, (void*)p);
	}
	i = 0; 
	for(; i<PRODUCER_COUNT; i++){
		int *p = (int*)malloc(sizeof(int));
		*p = i;
		pthread_create(&thread[i+CONSUMER_COUNT], NULL, produce, (void*)p);
	}	
	for(i=0; i<CONSUMER_COUNT+PRODUCER_COUNT; i++){
		pthread_join(thread[i], NULL);
	}
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
}
