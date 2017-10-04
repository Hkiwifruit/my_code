#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main()
{
	int fds[2];
	if(pipe(fds) == -1)perror("pipe");

	char buf[1024] = {};
	while(fgets(buf, 1024, stdin) != NULL){
		if(write(fds[1], buf, strlen(buf)) == -1)perror("write");
		if(read(fds[0], buf, strlen(buf)) == -1)perror("read");
		write(1, buf, strlen(buf));
		memset(buf, 0, sizeof(buf));
	}
	close(fds[1]);
	close(fds[0]);
}
