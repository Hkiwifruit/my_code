#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>


int main()
{
	int shmid = shmget(1234, 0, 0);
	if(shmid == -1){
		perror("shmget");
		exit(1);
	}
	int semid = semget(1234, 0, 0);
	if(semid == -1)
		perror("semget"),exit(1);

	int *p = (int*)shmat(shmid, NULL, 0);
	if(p == NULL) perror("shmat"),exit(1);

	struct sembuf sb[1];
	sb[0].sem_num = 0;
	sb[0].sem_op = 1;
	sb[0].sem_flg = 0;
	while(1){
		sleep(1);
		printf("%d\n", *p);

		//V操作
		semop(semid, sb, 1);
	}
}
