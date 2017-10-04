#include"comn.h"
int main()
{
	int msgid = getMsgQueue();

	char buf[1024];
	while(1){

		printf("Please Enter** ");
		fflush(stdout);
		ssize_t s = read(0, buf, sizeof(buf)-1);
		
		if(s>0){
			buf[s-1] = 0;
			sendMsg(msgid, CLIENT_TYPE, buf);
		}

		recvMsg(msgid, SERVER_TYPE, buf);
		printf("server say**%s\n", buf);
	}
	//destroyMsgQueue(msgid);
	return 0;
}
