#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
	int msg = msgget(1234, IPC_CREAT|0644);
	if(msg == -1){
		perror("msgget");
		exit(1);
	}
	printf("success\n");
}
