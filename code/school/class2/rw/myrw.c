#include<stdio.h>
#include<pthread.h>

int book=0;
pthread_rwlock_t rwlock;

void *myread(void *arg)
{
	while(1){
		if(pthread_rwlock_tryrdlock(&rwlock) != 0){
			printf("reader say*** writer is writing!\n");
		}else{
			
			printf("read book is :%d\n", book);
			sleep(3);
			pthread_rwlock_unlock(&rwlock);
		}
	}
}

void *mywrite(void *arg)
{
	while(1){
		sleep(1);
		if(pthread_rwlock_trywrlock(&rwlock) != 0){
			printf("write say&& reader is reading!\n");
		}else{
			book++;
		}
	}
}

int main()
{
	pthread_rwlock_init(&rwlock, NULL);
	pthread_t w, r;
	pthread_create(&w, NULL, mywrite, NULL);
	pthread_create(&r, NULL, myread, NULL);

	pthread_join(r, NULL);
	pthread_join(w, NULL);
	pthread_rwlock_destroy(&rwlock);
}
