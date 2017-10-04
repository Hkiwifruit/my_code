#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>

int main()
{
	int fds[2]={0,0};
	if(pipe(fds) < 0){
		perror("pipe");
		return 1;
	}


	pid_t id = fork();
	if(id==0){//child
		close(fds[0]);
		char msg[] = "hello pid! I am child";
		int i=0;
		while(1){
			write(fds[1], msg, strlen(msg));
			sleep(1);
		}
	}else{//father
		close(fds[1]);
		close(fds[0]);
		char buf[1024];
		int i = 0;

		while(1){
			ssize_t s = read(fds[0], buf, sizeof(buf));
			if(s>0){
				buf[s] = 0;
				printf("client->father# %s\n",buf);
			}
			if(i++>5){
				break;
			}
		}
		close(fds[0]);
		int status = 0;

		pid_t ret= waitpid(id, &status, 0);
		printf("status: %d, sig: %d, exitcode: %d\n",status, status&0xff,(status>>8)&0xff);
	}
	return 0;
}


