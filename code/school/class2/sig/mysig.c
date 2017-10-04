#include<stdio.h>
#include<signal.h>

void handler(int i)
{
	printf("get sig is: %d\n", i);
}

int main()
{
	int i = 0;
	for( ; i<32; i++){
	signal(i, handler);
	}
	while(1);
//	while(1){
//		printf("********************\n");
//		sleep(1);
//	}
	return 0;
}
