#ifndef _COMN_H_
#define _COMN_H_

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>

#include<stdio.h>

#define PATHNAME "." //present file
#define PROJ_ID 0x6666

#define SERVER_TYPE 1
#define CLIENT_TYPE 2

struct msgbuf {
         long mtype;       /* message type, must be > 0 */
		char mtext[1024];    /* message data */
};
	

int creatMsgQueue();
int destroyMsgQueue(int msgid);
int sendMsg(int msgid, int type, const char*msg);
int recvMsg();

#endif
