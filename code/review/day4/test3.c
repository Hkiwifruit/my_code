#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
	pid_t pid;
	if((pid == fork())== -1){
		exit(1);
	}else if(pid > 0){
		sleep(60);
		exit(2);
	}else{
		int status;
		pid_t c = wait(&status);
		if (!(status & 0xFF) )
		    printf("child exit code:%d\n", (status>>8)&0xFF);
		else 
			printf("not normal %d", status&0X7F);
	}
}
