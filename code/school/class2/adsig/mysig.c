#include<stdio.h>
#include<signal.h>
#include<unistd.h>

//void myhandler(int sig)
//{
//	printf("get a sig:%d\n", sig);
//}
//
//int mysleep(int timeout)
//{
//	struct sigaction act, oact;
//	act.sa_handler=myhandler;
//	sigemptyset(&act.sa_mask);
//	act.sa_flags = 0;
//	sigaction(SIGALRM, &act, &oact);
//
//	alarm(timeout);
//	pause();
//	int ret = alarm(0);
//	sigaction(SIGALRM, &oact, NULL);
//	return ret;
//
//}
//
//int main()
//{
//	while(1){
//		mysleep(3);
//		printf("I am wake up!\n");
//	}
//	return 0;
//}


void showpending(sigset_t *set)
{
	int i=1;
	for(; i<=31; i++){
		if(sigismember(set, i)){
			putchar('1');
		}else{
			putchar('0');
		}
	}
	printf("\n");
}

void handler(int sig){

}

int main()
{
	signal(2, handler);
	sigset_t bset, obset;
	sigemptyset(&bset);
	sigemptyset(&obset);

	sigaddset(&bset, 2);
	sigprocmask(SIG_SETMASK, &bset, &obset);

	sigset_t pending;
	int c=0;
	while(1){
		sigpending(&pending);
		showpending(&pending);
		sleep(1);
		if(c++ == 10){
			sigprocmask(SIG_SETMASK, &obset, NULL);
		}
	}
	return 0;
}
