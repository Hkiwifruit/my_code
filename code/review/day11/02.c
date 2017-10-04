#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

void handler(int s)
{
	if(s == SIGINT){
		printf("recv %d\n", s);
	}else{
		sigset_t set;
		sigemptyset(&set);
		sigaddset(&set, SIGINT);
		sigprocmask(SIG_UNBLOCK, &set, NULL);
	}
}

void print_set(sigset_t* set)
{
	int i;
	for(i=1; i<NSIG; i++){//信号最大数
		if(sigismember(set, i)){
			printf("1");
		}else{
			printf("0");
		}
	}
	printf("\n");
}

int main(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);

	sigset_t bset, pset;//定义信号集
	sigemptyset(&bset);
	sigaddset(&bset, SIGINT);//将int信号加入信号集

	sigprocmask(SIG_BLOCK, &bset, NULL);//将之设置到内核

	for( ; ; ){
		sigpending(&pset);//获得内核的未决信号集
		print_set(&pset);
		sleep(1);
	}
}
