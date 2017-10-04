#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>

void sem_p(int semid)
{
	struct sembuf sb[1] = {0, -1, 0};
	semop(semid, sb, 1);
}

void sem_v(int semid)
{
	struct sembuf sb[1] = {0, +1, 0};
	semop(semid, sb, 1);
}

union semum{
	int val;
}

int sem_open(key_t key)
{
	int r = semget(key, 0, 0);
	return r;
}

int sem_getval(int semid)
{
	return semctl(semid, 0, GETVAL, 0);
}

void sem_p(int semid)
{
	struct sembuf sb[1] = {0, -1, 0};
	semop(semid, sb, 1);
}

vodi sem_v(int semid)
{
	struct sembuf sb[1] = {0, +1, 0};
	semop(semid, sb, 1);
}

int main(void)
{
	int semid = sem_open(1234);
	sem_v(semid);
	printf("value = %d\n", sem_getval(semid));
}
