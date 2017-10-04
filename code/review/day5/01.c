#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char* argv[8];
int argc = 0;
char buf[1024] = {0};

void parse(char* arg)
{
	int i = 0;
	int status = 0;
	for(; buf[i] != 0; i++){
		if(status == 0 && !isspace(buf[i])){
			argv[argc++] = buf+i;
			status = 1;
		}else if(isspace(buf[i])){
			buf[i] = 0;
			status = 0;
		}
	}
	argv[argc] = NULL;
}

void do_exec()
{
	pid_t pid;
	if((pid = fork()) == -1){
		exit(1);
	}
	if(pid == 0){
		if(execvp(argv[0], argv) == -1){
			printf("commnad not found!\n");
			exit(2);
		}
	}

	wait(NULL);
}

int main(void )
{
	

	while(1){
		printf("Enter>>>>>>>: ");
		memset(buf, 0x00, sizeof(buf));
		scanf("%[^\n]", buf);
		scanf("%*C", buf);
		if(strncmp(buf, "exit", 4) == 0)
			exit(3);
		printf("[%s]\n", buf);
		parse(buf);
		do_exec();
	}
}
