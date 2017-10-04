#include <stdio.h>
#include <time.h>
#include <signal.h>

int X = 0;
int V = 0;

void handler()
{
	printf("\nV=%d, X=%d\n", V, X);
}

int main()
{
	alarm(20);
	signal(SIGALRM, handler);

	int i;
	srand(time(NULL));

	int left, right, ret;
	for(i =0 ;i<10; i++){
		left = rand()%10;
		right = rand()%10;
		printf("%d + %d = ",left, right);
		scanf("%d", &ret);
		if(ret == left +right){
			V++;
		}else{
			X++;
		}
	}
	printf("\nV = %d, X = %d\n", V, X);
}
