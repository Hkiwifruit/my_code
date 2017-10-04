#ifndef _HTTPD_H_
#define _HTTPD_H_

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int startup(const char* ip, int port);
void* handler_request(void *arg);

#endif
