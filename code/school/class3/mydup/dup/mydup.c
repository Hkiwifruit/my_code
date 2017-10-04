#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	umask(0);
	int fd = open("./log", O_CREAT | O_RDWR, 0666);
	if(fd < 0){
		perror("open");
		exit(1);
	}

	close(1);
	int ret = dup(fd);
	if(ret == -1){
		perror("dup");
		exit(-1);
	}
	int i = 0;
	char* msg="hello world!\n";
	while(i++ < 10){
		write(ret, msg, strlen(msg));
	}
	return 0;
}
