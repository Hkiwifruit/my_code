#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main()
{
	umask(0);
	if(mkfifo("./mypipe", 0666|S_IFIFO) < 0){
		perror("mkfifo");
		return 1;
	}
	int fd = open("./mypipe", O_RDONLY);
	if(fd< 0){
		perror("open");
		return 2;
	}

	char buf[1024];
	while(1){
		ssize_t s = read(fd, buf, sizeof(buf)-1);
		if(s > 0){
			buf[s] = 0;
			printf("client say# %s",buf);
		}else if(s == 0){
			printf("client quit!   serve quit\n");
			return 2;
		}
	}

}
