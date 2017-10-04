#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
	int shmid = shmget(1234, 0, 0);
	if(shmid == -1){
		perror("shmget");
		exit(1);
	}
	printf("open share memory ok\n");

	stu_t *ps = (stu_t*)shmat(shmid, NULL, 0);
	if(ps == NULL){
		perror("shmat");
		exit(1);
	}

	int i = 0;
	while(1){
		ps->name[0] = 'a'+i%26;
		ps->age = ++i%200;
		ps->gender = 0;
		sleep(1);
		printf("write ok\n");
	}

	shmdt(ps);
}
