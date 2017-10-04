#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
	pid_t id = fork();
	if(id==0){
		printf("child is running!\n");
		sleep(1);
		//..execl("/bin/ls","ls","-a","-l","-n","-i",NULL);
		//execlp("ls","ls","-a","-l","-n","-i",NULL);
		char* argv[]={
			"ls",
			"-l",
			"-a",
			"-n",
			"-i",
			NULL
		};
		execv("/bin/ls",argv);
		printf("child running done!\n");
		exit(1);
	}else{
		pid_t ret = waitpid(id,NULL,0);
		if(ret > 0){
			printf("father wait success!\n");
		}else{
			printf("child is quit not normal!\n");
		}
	}
}
