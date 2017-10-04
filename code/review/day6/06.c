#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define ERR_EXIT(msg)\
	do{\
		fprintf(stderr, "[%s][%d] %s:%s\n", __FILE__, __LINE__,msg,\
				strerror(errno));\
				exit;\
	}while(0);

int main(int argc, char* argv[])
{
	if(argc < 2){
		fprintf(stderr, "usage%s  file\n", argv[0]);
		exit(1);
	}

	struct stat sbuf;

	if(stat(argv[1], &buf) == -1){
		ERR_EXIT("exit");
	}

	switch (sbuf.st_mode & S_IFMT){
		case 
	}
}
