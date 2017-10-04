#include"comm.h"

int main()
{
	int shmid = creatShm(4097);
	sleep(3);
	char* addr = (char*)shmat(shmid, NULL, 0);
	
//	printf("server is done...!\n");
	
	int i = 0;
	while(1){
		sleep(1);
		printf("%s\n", addr);
	}
	shmdt(addr);
	destoryShm(shmid);
	return 0;
}
