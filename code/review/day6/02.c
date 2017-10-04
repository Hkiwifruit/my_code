#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

#define ERR_EXIT(msg)\
	do{\
		fprintf(stderr, "[%s][%d] %s:%s\n", __FILE__, __LINE__,msg,\
				strerror(errno));\
				exit;\
	}while(0);

int main()
{
	int fd = open("test.txt", O_RDWR);
	if(fd == -1)
		ERR_EXIT("open");
	close(1);
	int nfd = dup(fd);
	char buf[1023] = {};
	sprintf(buf, "ABCDEF", 6);

}
