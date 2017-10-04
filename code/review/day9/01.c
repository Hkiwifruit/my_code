#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

typedef struct{
	char name[20];
	int age;
	int gender;
}stu_t;

int main(void)
{
	int shmid = shmget(1234,sizeof(stu_t), IPC_CREAT | 0644);
	if(shmid == -1){
		perror("shmget");
		exit(1);
	}
	printf("create ok\n");
}
