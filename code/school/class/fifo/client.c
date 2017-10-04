#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
int main()
{
	int fd = open("./mypipe", O_WRONLY);
	if(fd< 0){
		perror("open");
		return 2;
	}

	char buf[1024];
	while(1){
		printf("please input:");
		fflush(stdout);
		ssize_t s = read(0, buf, sizeof(buf)-1);
		if(s > 0){
			buf[s] = 0;
			write(fd, buf, strlen(buf));
		}
	}
	close(fd);
	return 0;
}
