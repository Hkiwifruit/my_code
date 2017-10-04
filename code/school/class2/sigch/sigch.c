#include<stdio.h>
#include<signal.h>
#include<stdlib.h>

void handler(int sig)
{
	printf("get a sig: %d, pid: %d\n", sig, getpid());
	pid_t ret = waitpid(-1, NULL, 0);
	if(ret > 0){
		printf("wait success: %d\n", ret);
	}else{
		printf("wait failed\n");
	}
}

int main()
{
	signal(SIGCHLD, handler);
	pid_t id = fork();
	if(id == 0){
		//child
		printf("I am child: %d\n", getpid());
		sleep(3);
		exit(1);
	}else{
		//father
		printf("I am father: %d\n", getpid());
		waitpid(id, NULL, 0);
	}
}
