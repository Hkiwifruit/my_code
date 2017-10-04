#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

union semun{
	int val;
};

int sem_create(key_t key)
{
	int r = semget(key, 1, IPC_CREAT | 0644);
	return r;
}

int sem_open(key_t key)
{
	int r = semget(key, 0, 0);
	return r;
}

int sem_setval(int semid, int val)
{
	union semun su;
	su.val = val;

	return semctl(semid, 0, SETVAL, su);
}

int sem_getval(int semid)
{
	return semctl(semid, 0, GETVAL, 0);
}

int main(void)
{
	//int semid = sem_create(1234);
	int semid = sem_open(1234);
	if(semid == -1){
		perror("sem_open");
		exit;
	}
	printf("create sem ok\n");
	sem_setval(semid, 5);

	printf("value = %d\n", sem_getval(semid));
}
