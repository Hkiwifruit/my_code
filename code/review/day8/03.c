#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
	long channel;
	char buf[1024];
}msg_t;

int main(int argc, char* argv[])
{
	int channel;
	msg_t cache;

	int msgid = msgget(1234, 0);
	if(msgid == -1)perror("msgget");

	channel = getopt(argc, argv, "t:");
	if(channel == -1){
		fprintf(stderr, "usage:%s -t id\n", argv[0]);
		exit(0);
	}

	if(channel == '?')
		fprintf(stderr, "parse err\n"),exit(1);

	cache.channel = atoi(optarg);
	printf("info\n");
	scanf("%[^\n]%*c", cache.buf);

	if(msgsnd(msgid, &cache, strlen(cache.buf), 0) == -1){
		printf("msg is failing\n");
		exit(2);
	}


//	while(1){
//		r = getopt(argc, argv, "ab:c");
//		if(r == -1){
//			printf("parse end\n");
//			break;
//		}
//		if(r == '?'){
//			printf("cannot parse\n");
//			break;
//		}
//		switch(r){
//			case 'a':
//				printf("AAAAAAAAA\n");
//				break;
//			case 'b':
//				printf("BBBBBBBBB\n");
//				break;
//			case 'c':
//				printf("CCCCCCCCC\n");
//				break;
//		}
//	}
}
