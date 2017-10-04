#include"comn.h"


static int comnMsgQueue(int flags)
{
	key_t _key = ftok(PATHNAME, PROJ_ID);
	if(_key < 0){
	
		perror("ftok");
		return -1;
	}
	int msgid = msgget(_key, flags);
	if(msgid < 0){
		perror("msgget");
		return -2;
	}
	return msgid;

}

int creatMsgQueue()
{
	return comnMsgQueue(IPC_CREAT | IPC_EXCL | 0666);
}

int getMsgQueue()
{
	return comnMsgQueue(IPC_CREAT);
}

int destroyMsgQueue(int msgid)
{
	if(msgctl(msgid, IPC_RMID, NULL)<0){
		perror("msgctl");
		return -1;
	}
	return 0;
}

int sendMsg(int msgid, int type, const char *msg)
{
	struct msgbuf _mb;
	_mb.mtype = type;
	strcpy(_mb.mtext, msg);
	if(msgsnd(msgid, &_mb, sizeof(_mb.mtext), 0)<0){
		perror("msgbuf");
		return -1;
	}
	return 0;
}

int recvMsg(int msgid, int type, char *out)
{
	struct msgbuf _mb;
	if(msgrcv(msgid, &_mb, sizeof(_mb.mtext), type, 0)<0){
		perror("msgrcv");
		return -1;
	}
	strcpy(out, _mb.mtext);
	return 0;
}
