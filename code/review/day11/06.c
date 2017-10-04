#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *hand1(void* arg)
{
	while(1){
		printf("I am lao da\n");
	}
}
void *hand2(void* arg)
{
	while(1){
		printf("I am lao er\n");
	}
}
void *hand3(void* arg)
{
	while(1){
		printf("I am lao san\n");
	}
}
void *hand4(void* arg)
{
	while(1){
		printf("I am lao si\n");
	}
}

int main(void)
{
	pthread_t a, b, c, d;
	pthread_create(&a, NULL, hand1, NULL);
	pthread_create(&b, NULL, hand2, NULL);
	pthread_create(&c, NULL, hand3, NULL);
	pthread_create(&d, NULL, hand4, NULL);

	while(1){
		printf("I am boss\n");
	}

	ptread_join(&a, NULL);
	ptread_join(&b, NULL);
	ptread_join(&c, NULL);
	ptread_join(&d, NULL);
}
