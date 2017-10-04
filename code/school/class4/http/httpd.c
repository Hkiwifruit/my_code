#include "httpd.h"

const char* status_line = "http/1.0 200 ok";
const char* type_line = "Content-Type:text/html;charset=ISO-8859-1\r\n";
const char* blank_line = "\r\n";

#define SIZE 1024

void clear_header(int fd);
static int  exe_cgi(int fd, char* method, char* query_string, char* path);
int echo_www(int fd, char* path, size_t size);
void* handler_request(void *arg);
int startup(const char* ip, int port)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0){
		perror("socket");
		exit(2);
	}

	int opt = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
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
	int ret = -1;
	do{
	//	printf("clear\n");
		ret = get_line(fd, buf, SIZE);
	}while((ret > 0) && strcmp(buf, "\n"));
}

static int exe_cgi(int fd, char* method, char* query_string, char* path)
{
	printf("Enter cgi\n");
	int content_length = -1;
	char method_env[SIZE/10];
	char query_string_env[SIZE];
	char content_length_env[SIZE/10];

	int input[2];
	int output[2];
	if(strcasecmp(method, "GET") == 0){
		clear_header(fd);
	}else{
		int ret = -1;
		char buf[SIZE];
		do{
			ret = get_line(fd, buf, sizeof(buf));
			if(ret > 0 && strncasecmp(buf, "Content-Length: ", 16) == 0){
				content_length = atoi(buf+16);
				printf("%d\n", content_length);
			}
		}while(ret > 0 && strcmp(buf, "\n"));
		if(content_length == -1){
			printf("content_length = %d\n", content_length);
			return 10;
		}
	}
		send(fd, status_line, strlen(status_line), 0);
		send(fd, type_line, strlen(type_line), 0);
		send(fd, blank_line, strlen(blank_line), 0);

		if(pipe(input) < 0){
			perror("pipe1");
			return ;
		}
		if(pipe(output) < 0){
			perror("pipe2");
			return ;
		}
		
		pid_t id = fork();

		if(id < 0){
			perror("fork err");
			return ;
		}
		if(id == 0){
			close(input[1]);
			close(output[0]);

			sprintf(method_env, "METHOD=%s", method);
			putenv(method_env);

			if(strcasecmp(method, "GET") == 0){
				sprintf(query_string_env, "QUERY_STRING=%s", query_string);
				putenv(query_string_env);
				
			}else{//POST
				sprintf(content_length_env, "CONTENT_LENGTH=%d", content_length);
				printf("ccccccccccccccccccccc%s", content_length_env);
				putenv(content_length_env);
			}
			dup2(input[0], 0);
			dup2(output[1], 1);
			execl(path, path, NULL);
			printf("execl error\n");
			exit(1);
		}else{
			close(input[0]);
			close(output[1]);
			char c = '\0';
			if(strcasecmp(method, "POST") == 0){//POST
				int i = 0;
				for( ; i < content_length; i++){
					recv(fd, &c, 1, 0);
					write(input[1], &c, 1);
				}
			}else{
				c = '\0';
				while(read(output[0], &c, 1))
					send(fd, &c, 1, 0);
			}
			waitpid(id, NULL, 0);
			close(input[1]);
			close(output[0]);
		}
}

static void echo_string(int sock)
{
}

int echo_www(int fd, char* path, size_t size)
{
	int fds = open(path, O_RDONLY);
	if(fd < 0){
		echo_string(fd);
		//print_log(strerror(errno), FATAL);
		return 8;
	}
	const char* echo_line = "HTTP/1.0 200 OK\r\n";
	send(fd, echo_line, strlen(echo_line), 0);
	char* blank_line = "\r\n";
	send(fd, blank_line, strlen(blank_line), 0);
	if(sendfile(fd, fds, 0, size) < 0){
		echo_string(fd);
		//print_log(strerror(errno), FATAL);
		return 9;
	}
	close(fds);
	return 0;
}

void* handler_request(void *arg)
{
	int fd = (int)arg;
	char buf[SIZE];
	char method[SIZE/20];
	char url[SIZE];
	int err_code = 200;
	char* query_string = NULL;
	char path[SIZE];
	int cgi = 0;

	if(get_line(fd, buf, sizeof(buf)) < 0){
		err_code = 404;
		printf("err_codellllllllllllllll\n");
		goto end;
	}
	int i = 0, j = 0;
	while(j < sizeof(method)-1 && i < sizeof(buf) && !isspace(buf[i])){
		method[j] = buf[i];
		i++, j++;
	}
	method[j] = '\0';

	if(strcasecmp(method, "GET") && strcasecmp(method, "POST")){
		err_code = 404;
		goto end;
	}
	if(strcasecmp(method, "POST") == 0){
		cgi = 1;
	}
	while(i < sizeof(buf) && isspace(buf[i])){
		i++;
	}
	j = 0;
	while(j < sizeof(url) && i < sizeof(buf) && !isspace(buf[i])){
		url[j] = buf[i];
		i++, j++;
	}
	url[j] = '\0';
	if(strcasecmp(method, "get") == 0){
		query_string = url;
		while(*query_string){
			if(*query_string == '?'){
				*query_string = '\0';
				query_string++;
				cgi = 1;
				break;
			}
			query_string++;
		}
	}else{
		cgi = 1;
	}

	sprintf(path, "wwwroot%s", url);
	if(path[strlen(path)-1] == '/'){
		strcat(path, "index.html");
	}
	
	struct stat s;
	if(stat(path, &s) != 0){
		err_code = 404;
		goto end;
	}else{
		if(S_ISDIR(s.st_mode)){
			strcat(path, "/index.html");
		}else if(s.st_mode & S_IXUSR || s.st_mode & S_IXGRP || s.st_mode & S_IXOTH){
			cgi = 1;
		}else{
		}
		if(cgi == 1){
			exe_cgi(fd, method, query_string, path);
		}else{
			printf("method:%s, url:%s, path:%s,cgi: %d, query_string: %s\n", method, url,path,cgi,query_string);
			clear_header(fd);
			echo_www(fd, path, s.st_size);
		}
	}

end:
	//echo_client(fd, err_code);
	close(fd);
	return (void*)0;
}
