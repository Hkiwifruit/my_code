#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

typedef struct{
	int a;
	int b;
}test_t;

test_t g_data = {};

void unsafe()
{
	printf("a = %d, b = %d\n", g_data.a, g_data.b);
}

void handler(int s)
{
	unsafe();
	alarm(1);
}

int main()
{
	test_t zeros = {0, 0};
	test_t ones = {1, 1};

	signal(SIGALRM, handler);
	alarm(1);
	while(1){
		g_data = zeros;
		g_data = ones;
	}
}
