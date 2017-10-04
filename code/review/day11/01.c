#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int s)
{
	printf("get %d\n", s);
}

int main(void)
{
	pid_t pid;

	signal(SIGTERM, handler);
	if((pid = fork()) == -1)perror("fork"),exit(1);

	if(pid == 0){
		sleep(5);
		kill(getpid(), 15);
	}else{
		while(1){
			printf(".");
			fflush(stdout);
			sleep(1);
		}
	}
}
