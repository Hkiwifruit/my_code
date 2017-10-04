#include "httpd.h"


#define SIZE 1024

int startup(const char* ip, int port)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0){
		perror("socket");
		exit(2);
	}

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = inet_addr(ip);
	local.sin_port = htons(port);
	if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0){
		perror("bind");
		exit(3);
	}
	
	if(listen(sock, 5) < 0){
		perror("listen");
		exit(4);
	}

	return sock;
}

static int get_line(int sock, char buf[], int size)
{
	int i = 0;
	char c = '\0';
	while(i < size-1 &&c != '\n'){
		ssize_t s = recv(sock, &c, 1, 0);
		if(s > 0){
			if(c == '\r'){
				recv(sock, &c, 1, MSG_PEEK);
				if(c == '\n'){
					recv(sock, &c,1, 0);
				}else{
					c = '\n';
				}
			}
			buf[i++] = c;
		}else{
			return -1;
		}
	}
	buf[i] = '\0';
	return i;
}

void clear_header(int fd)
{
	char buf[SIZE];
	int ret = 0;
	do{
	//	printf("clear\n");
		ret = get_line(fd, buf, SIZE);
	}while((ret > 0) && strcmp(buf, "\n"));
}

void echo_www(int fd, char* path, size_t size)
{
	printf("%s\n", path);
	int fds = open(path, O_RDWR);
	char* msg = "http/1.0 202 ok\n";
	char* blank = "\n";
	send(fd, msg, strlen(msg), 0);
	send(fd, blank, strlen(blank), 0);
	printf("fds = %d\n", fds);
	if( sendfile(fd, fds, 0, size) == -1)
		printf("send fail\n");
}

void* handler_request(void *arg)
{
	int fd = (int)arg;
	char buf[SIZE];
	char method[SIZE/100];
	char url[SIZE];
	int err_code = 200;
	char* query_string;
	char path[SIZE];
	int cgi = 0;

	if(get_line(fd, buf, sizeof(buf)) < 0){
		err_code = 404;
		goto end;
	}
	printf("%s\n",buf);
	int i = 0, j = 0;
	while(j < sizeof(method) && i < sizeof(buf) && !isspace(buf[i])){
		method[j] = buf[i];
		i++, j++;
	}
	method[j] = '\0';
	while(i < sizeof(buf) && isspace(buf[i])){
		i++;
	}
	j = 0;
	while(j < sizeof(url)-1 && i < sizeof(buf) && !isspace(buf[i])){
		url[j] = buf[i];
		i++, j++;
	}
	url[j] = '\0';
	if(strcasecmp(method, "GET") && strcasecmp(method, "POST")){
		err_code = 404;
		goto end;
	}
	if(strcasecmp(method, "get") == 0){
		query_string = url;
		while(*query_string){
			if(*query_string == '?'){
				*query_string = '\0';
				cgi = 1;
				break;
			}
			query_string++;
		}
	}else{
		cgi = 1;
	}

	struct stat s;
	sprintf(path, "wwwroot%s", url);
	if(path[strlen(path)-1] == '/'){
		printf("path : %s\n", path);
		strcat(path, "index.html");
	}else{
		if(stat(path, &s) < 0){
			err_code = 404;
			printf("error 404\n");
			goto end;
		}else if(S_ISDIR(s.st_mode)){
			strcat(path, "/index.html");
		}else if(s.st_mode & S_IXUSR || s.st_mode & S_IXGRP || s.st_mode & S_IXOTH){
			cgi = 1;
		}
	}
	if(cgi == 1){
	}else{
		clear_header(fd);
		printf("%s\n", path);
		echo_www(fd, path, s.st_size);
	}

end:
	//echo_client(fd, err_code);
	close(fd);
	return (void*)0;
}

