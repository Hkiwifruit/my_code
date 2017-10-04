#include"comm.h"

int main()
{
	int shmid = getShm(4097);
	sleep(3);
	char* addr = (char*)shmat(shmid, NULL, 0);
	
	int i = 0;
	while(1){

		addr[i] = 'A' + i;
		i++;
		addr[i] = 0;
		sleep(1);
	}
//	printf("server is done...!\n");

	shmdt(addr);
//	destoryShm(shmid);
	return 0;
}
