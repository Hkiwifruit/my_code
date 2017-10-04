#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

union semun{
	int val;
};


int main(void)
{
	//创建共享内存
	int shmid = shmget(1234, sizeof(int), IPC_CREAT | 0644);
	if(shmid == -1){
		perror("shmget");
		exit(1);
	}
	//创建信号量
	int semid = semget(1234, 1, IPC_CREAT | 0644);
	if(semid == -1){
		perror("semget");
		exit(1);
	}
	//设置信号量
	union semun su;
	su.val = 1;
	semctl(semid, 0, SETVAL, su);

	int* p = (int*)shmat(shmid, NULL, 0);
	if(p = (void*)-1)perror("shmat"),exit(1);
	int i = 1;
	struct sembuf sb[1];
	while(1){	
		sb[0].sem_num = 0;
		sb[0].sem_op = -1;
		sb[0].sem_flg = 0;

		//P操作
		semop(semid , sb, 1);
		*p = i++;
	}
}

