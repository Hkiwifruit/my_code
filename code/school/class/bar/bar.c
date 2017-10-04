#include<stdio.h>
#include<unistd.h>
#include<string.h>

int main()
{
	int i = 0;
	char label[4] = {'|', '/', '-', '\\'};
	char bar[102];
	bar[0] = 0;
	while(i <= 100){
		printf("[\033[1m%-100s\033[1m][%d%%][%c]\r", bar, i, label[i%4]);
		fflush(stdout);
		bar[i] = '#';
		i++;
		bar[i] = 0;
		usleep(100000);
	}
	printf("\n\033[1m");
	return 0;
}


