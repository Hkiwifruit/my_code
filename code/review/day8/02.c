#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
	int msg = msgget(1234, 0);
	if(msg == -1){
		perror("msgget");
		exit(1);
	}
	printf("open msg ok!\n");

	msgctl(msg, IPC_RMID, NULL);
}
