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
	if(fd == -1)ERR_EXIT("open");

	struct flock fl;
	fl.l_type = F_WRLCK;
	fl.l_whence = SEEK_SET;
	fl.l_start = 0;
	fl.l_len = 0;
	
	if(fcntl(fd, F_SETLKW, &fl) == 0){
		printf("lock ok\n");
		getchar();
		fcntl(fd, F_SETLKW, &fl);
		fl.l_type = F_UNLCK;
	}else{
		ERR_EXIT("fcntl");
	}
}
