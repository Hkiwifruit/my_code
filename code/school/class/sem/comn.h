#ifndef _COMN_H_
#define _COMN_H_

#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<string.h>

#define PATHNAME "."
#define PROJ_ID 0X6666


union semun {
	int val;    /* Value for SETVAL */
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;  /* Array for GETALL, SETALL */
	struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */			
};



int creatSem(int nums);
int getSemset(int nums);
int destorySemSet(int semid);
int P(int semid, int num);
int V(int semid, int num);
int InitSemSet(int semid, int num, int val);

#endif
