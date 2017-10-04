/*
 *信号处理方式：
	1，缺省处理方式
	2，忽略
		SIGKILL//不能忽略
		SIGSTOP//不能忽略
	3，捕获
		SIGKILL
		SIGSTOP
	安装信号：
	void (*signal（int sig， void(*handler)(int)))(int);

 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void handler(int s)
{
	printf("你等着！\n");
}

int main()
{
	__sighandler_t old;
	old = signal(SIGINT, /*handler*/SIG_IGN);
	if(old == SIG_ERR)
		perror("signal"),exit(1);
	while(1){
		if(getchar() == '\n')
			break;
	}

	signal(SIGINT, old);

	for(;;){
		printf("哈哈哈 来呀！\n");
		sleep(1);
	}
}
