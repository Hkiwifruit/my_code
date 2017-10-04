#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

int main()
{
	int sv[2];
	int ret = socketpair(PF_LOCAL, SOCK_STREAM, 0, sv);
	if(ret != 0){
		perror("socketpair");
		exit(1);
	}

	pid_t id = fork();
	if(id < 0){
		perror("fork");
		exit(2);
	}else if(id == 0){//child
		close(sv[0]);
		const char buf[512];
		char* msg = "I am your child!";
		while(1){
			write(sv[1], msg, strlen(msg));
			read(sv[1], buf, sizeof(buf));
			sleep(1);
			printf("Father say#%s\n", buf);
		}
	}else{//father
		close(sv[1]);
		const char buf[512];
		char* msg = "I am your father!";
		while(1){
			read(sv[0], buf, sizeof(buf));
			printf("Child say: %s\n", buf);
			write(sv[0], msg, strlen(msg));
		}
	}
	return 0;
}
