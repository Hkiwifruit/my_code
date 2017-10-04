#include <stdio.h>
#include <unistd.h>

int main()
{
	//printf("pid = %d\n", getpid());
	//printf("ppid = %d\n", getppid());
	//
	
	pid_t pid;
	if((pid = fork()) == -1){
		
	}
	return 0;
}
