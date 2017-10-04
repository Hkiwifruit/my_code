#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

void handler(int s)
{
	wait(NULL);
	while(waitpid(-1, NULL, WNOHANG) == -1)//疯狂回收僵尸进程
		;
}

int main()
{
	//signal(SIGCHLD, handler);
	signal(SIGCHLD, SIG_IGN);//不管子进程死活，操作系统给他清理了
	pid_t pid = fork();

	if(pid == 0){
		int i = 0;
		for(;i < 5;i++){
			printf("$$$$$$\n");
			sleep(1);
		}
		exit(0);
	}

	for(;;){
		printf("￥￥￥￥￥\n");
		sleep(1);
	}
}
