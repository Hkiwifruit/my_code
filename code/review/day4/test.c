#include <stdio.h>
#include <unistd.h>

int main()
{
	//while(1);
	printf("%s\n", getenv());
//	pid_t pid;
//	
//	if(pid = fork()){
//		printf("I am father! pid = %d\n", getpid());
//		sleep(10);
//	}
//	else if(pid == 0){
//		printf("I am child! pid = %d\n", getpid());
//	}
	return 0;
}
