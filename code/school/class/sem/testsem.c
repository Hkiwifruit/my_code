#include"comn.h"
#include<unistd.h>


int main()
{
	int semid = creatSem(1);
	InitSemSet(semid, 0,1);

	if(fork() == 0){

		int _semid = getSemset(0);

		while(1){
			P(_semid, 0);
			printf("A");
			fflush(stdout);
			usleep(123456);
			printf("A ");
			fflush(stdout);
			usleep(545);
			V(_semid, 0);
		}
	}else{	
		while(1){
			P(semid, 0);
			printf("B");
			fflush(stdout);
			usleep(1245561);
			printf("B ");
			fflush(stdout);
			usleep(345);
			V(semid, 0);

		}
		wait(NULL);
	}

	destorySemSet(semid);
//	sleep(4);
//	printf("proc is running done!\n");
	return 0;
}
