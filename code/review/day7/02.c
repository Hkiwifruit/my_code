#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	int fds[2];
	if(pipe(fds) == -1)perror("pipe");

	char buf = "hello mei";
	pid_t pid = fork();
	if(pid == -1){
		perror("pipe");
	}
	if(pid == 0){
		close(fds[1]);
		write(fds[0], buf, strlen(buf));
		close(fds[0]);
	}
	else{
		close(fds[0]);
		char readbuf[1024] = {};
		if(read(fds[1], readbuf, strlen(readbuf)) == -1)
			perror("read");
		write(1, readbuf, strlen(readbuf));
		
		close(fds[1]);
	}
}
