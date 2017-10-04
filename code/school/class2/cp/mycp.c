#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>


typedef int DataType;

typedef struct ListNode
{
	DataType data;
	struct ListNode* next;
}ListNode;

ListNode* mylist=NULL;

static int IsEmpty(ListNode* list)
{
	if(list==NULL)
		return 0;
	else
		return 1;
}

ListNode* BuyNode(DataType x)
{
	ListNode* node=(ListNode*)malloc(sizeof(ListNode));
	node->data=x;
	node->next=NULL;
	return node;
}

void PushFront(ListNode** list, DataType x)
{
	if(IsEmpty(*list)){
		ListNode* newNode = BuyNode(x);
		newNode->next = *list;
		*list=newNode;
	}else{
		*list=BuyNode(x);
	}
	return;
}

ListNode* PopFront(ListNode** list)
{
	ListNode*next = NULL;
	if(IsEmpty(*list)){
		next=*list;
		*list=next->next;
	}
	return next;
}

void PrintList(ListNode* list)
{
	if(IsEmpty(list)){
		while(list){
			printf("%d ", list->data);
			list=list->next;
		}
		printf("\n");
	}
	return;
}


pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *consume()
{
	while(1){
		pthread_mutex_lock(&lock);
		ListNode *tmp = PopFront(&mylist);
		while(tmp ==NULL)
		{
			pthread_cond_wait(&cond,&lock);
			tmp = PopFront(&mylist);
		}
		printf("consume done...!%d\n", tmp->data);
		sleep(2);
		pthread_mutex_unlock(&lock);
		pthread_cond_signal(&cond);

	}
}

void* product()
{
	int i=0;
	while(1){
		pthread_mutex_lock(&lock);
		PushFront(&mylist, i);
		printf("product done...!%d\n", i++);
		pthread_cond_wait(&cond,&lock);
		pthread_mutex_unlock(&lock);
		pthread_cond_signal(&cond);
	}
}

int main()
{
	
	pthread_t c, p;
	pthread_create(&c, NULL, consume, NULL);
	pthread_create(&p, NULL, product, NULL);

	pthread_join(c, NULL);
	pthread_join(p, NULL);



//	int i=0;
//	ListNode* mylist=NULL;
//	while(i<10){
//		PushFront(&mylist, i++);
//		PrintList(mylist);
//		sleep(1);
//	}
//
//	while(i-->5){
//		PopFront(&mylist);
//		PrintList(mylist);
//		sleep(1);
//	}
	return 0;
}
