#include"comn.h"
int main()
{
	int msgid = getMsgQueue();

	char buf[1024];
	while(1){

		recvMsg(msgid, CLIENT_TYPE, buf);
		printf("client say**%s\n", buf);

		printf("Please Enter** ");
		fflush(stdout);
		ssize_t s = read(0, buf, sizeof(buf)-1);
		if(s>0){
			buf[s-1] = 0;
			sendMsg(msgid, SERVER_TYPE, buf);
		}


		sleep(1);
	}
	destroyMsgQueue(msgid);
	return 0;
}
