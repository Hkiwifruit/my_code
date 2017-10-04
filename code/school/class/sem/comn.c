#include"comn.h"


static int comnSem(int nums, int flags)
{
	key_t _k = ftok(PATHNAME, PROJ_ID);//使用ftok创key
	if(_k<0){
		perror("ftok");
		return -1;
	}

	//int semid = senget(_k, nums, IPC_CREAT | IPC_EXCL);
	int semid = semget(_k, nums, flags);
	if(semid<0){
		perror("semget");
		return -2;
	}
	return 0;
}

int creatSem(int nums)
{

	return comnSem(nums, IPC_CREAT | IPC_EXCL | 0x666);
}

int InitSemSet(int semid, int num, int val)
{
	union semun _un;
	_un.val = val;
	if(semctl(semid, num, SETVAL, _un) < 0){
		perror("semctl");
		return -1;
	}
	return 0;
}

int getSemset(int nums)
{
	return comnSem(nums, IPC_CREAT);
}

int destorySemSet(int semid)
{
	if(semctl(semid, 0, IPC_RMID) < 0)
	{
		perror("semctl");
		return -1;
	}
	return 0;
}

static int comnPV(int semid, int num, int op)
{
	struct sembuf _sf;
	memset(&_sf, 0, sizeof(_sf));
	_sf.sem_num = num;
	_sf.sem_op = op;
	_sf.sem_flg = 0;

	if(semop(semid, &_sf, 1) < 0){
		perror("semop");
		return -1;
	}
	return 0;
}
int P(int semid, int num)
{
	return comnPV(semid, num, -1);
}
int V(int semid, int num)
{
	return comnPV(semid, num, 1);
}
