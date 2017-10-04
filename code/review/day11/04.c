#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void handler(int s)
{
	printf("inter\n");
	sleep(5);
	printf("outer\n");
}

__sighandler_t mysignal(int no, __sighandler_t h)
{
	struct sigaction act, oldset;
	act.sa_handler = h;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(no, &act, &oldact);

	return oldact.sa_handler;
}

int main()
{
	struct sigaction act;
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGINT, &act, NULL);

	sigset_t bset;//定义信号集
	sigemptyset(&bset);//清空信号集
	sigaddset(&bset, SIGQUIT);//将3号信号加进去
	sigprocmask(SIG_BLOCK, &bset, NULL);//屏蔽信号。，

	for( ; ; ){
		printf(".");
		fflush(stdout);
		sleep(1);
	}
}
