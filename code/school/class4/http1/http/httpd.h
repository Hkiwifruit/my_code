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

#define SIZE 1024
#define NOTICE 0
#define WARNING 1
#define FATAL 2


int startup(const char* ip, int port);
void* handler(void *arg);
void echo_error(int fd, int error_code);
int echo_www(int fd, const char* path, int size);
int exe_cgi(int fd, const char *method, const char* path, const char* query_string);

#endif
