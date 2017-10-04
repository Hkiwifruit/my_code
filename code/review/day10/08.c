#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>

void handler(int s)
{
	printf("shi jian dao  %d\n", s);
}

int main(void)
{
	struct itimerval tv;
	tv.it_value.tv_sec = 0;
	tv.it_value.tv_usec = 1;

	tv.it_interval.tv_sec = 1;
	tv.it_interval.tv_usec = 0;

	signal(SIGALRM, handler);
	setitimer(ITIMER_REAL, &tv, NULL);

	for(;;){
	}
}
