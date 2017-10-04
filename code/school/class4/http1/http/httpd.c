#include "httpd.h"

static void show_404(int fd)
{
	const char* echo_header = "HTTP/1.0 404 NOT FOUND\r\n";
	send(fd,echo_header, strlen(echo_header), 0);
	const char* type = "Content-Type:text/html;charset=ISO-8859-1\r\n";
	send(fd, type, strlen(type), 0);
	const char* blank_line = "\r\n";
	send(fd, blank_line, strlen(blank_line), 0);

	const char* msg = "<html><h1>Page not found!</h1></html>";
	send(fd, msg, strlen(msg), 0);
}

void echo_error(int fd, int error_code)
{
	switch(error_code){
		case 404:
			show_404(fd);
			break;
		default:
			break;
	}

}

int startup(const char* ip, int port)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0){
		perror("sock");
		return 2;
	}

	struct sockaddr_in local;
	local. sin_family = AF_INET;
	local.sin_addr.s_addr = inet_addr(ip);
	local.sin_port = htons(port);

	int opt = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0){
		perror("bind");
		return 3;
	}

	if(listen(sock, 10) < 0){
		perror("listen");
		return 4;
	}

	return sock;
}

static int get_line(int fd, char*buf, int len)
{
	char c = '\0';
	int i = 0;
	while(c != '\n' && i < len-1){
		ssize_t s = recv(fd, &c, 1, 0);
		if(s > 0){
			if(c == '\r'){
				recv(fd, &c, 1, MSG_PEEK);
				if(c == '\n'){
					recv(fd, &c, 1, 0);
				}else{
					c = '\n';
				}
			}
			buf[i++]= c;
		}else{
			return -1;
		}
	}
	buf[i] = 0;
	return i;
}

void print_log(const char*msg, int level)
{
	const char *level_msg[] = {
		"NOTICE",
		"WARNING",
		"FATAL"
	};
	printf("[%s][%s]\n", msg, level_msg[level]);
}

int echo_www(int fd, const char* path, int size)
{
	int sock = open(path, O_RDONLY);
	if(sock < 0){
		print_log("open file failure!", FATAL);
		return 404;
	}

	const char* echo_line = "HTTP/1.0 200 OK\r\n";
	send(fd, echo_line, strlen(echo_line), 0);
	const char* blank_line = "\r\n";
	send(fd, blank_line, strlen(blank_line), 0);

	if(sendfile(fd, sock, NULL, size) < 0){
		print_log("send_file error", FATAL);
		return 404;
	}
	close(sock);
}

void drop_header(int fd)
{
	char buff[SIZE];
	int ret = -1;
	do{
		ret = get_line(fd, buff, sizeof(buff));
	}while(ret > 0 && strcmp(buff, "\n"));
}

int exe_cgi(int fd, const char* method,\
		const char *path, const char* query_string)
{
	int content_len = -1;
	char METHOD[SIZE/10];
	char QUERY_STRING[SIZE];
	char CONTENT_LENGTH[SIZE];

	if(strcasecmp(method, "get") == 0){
		drop_header(fd);
	}else{
		char line[SIZE];
		int ret = -1;
		do{
			ret = get_line(fd, line, sizeof(line));
			if(strncasecmp(line, "Content-length: ", 16) == 0)
				content_len = atoi(line+16);
		}while(ret > 0 && strcmp(line, "\n"));

		if(content_len == -1){
			echo_error(fd, 401);
			return -1;
		}
	}

	//printf("cgi:path:%s\n", path);

	int input[2];
	int output[2];
	pipe(input);
	pipe(output);

	const char* echo_line = "HTTP/1.0 200 OK\r\n";
	send(fd, echo_line, strlen(echo_line), 0);
	const char* type = "Content-Type:text/html;charset=ISO-8859-1\r\n";
	send(fd, type, strlen(type), 0);
	const char* blank_line = "\r\n";
	send(fd, blank_line, strlen(blank_line), 0);

	pid_t id = fork();
	if(id < 0){
		echo_error(fd, 501);
		return -2;
	}else if(id == 0){
		close(input[1]);
		close(output[0]);
		sprintf(METHOD, "METHOD=%s", method);

		putenv(METHOD);

		if(strcasecmp(method, "get") == 0){
			sprintf(QUERY_STRING, "QUERY_STRING=%s", query_string);
			putenv(QUERY_STRING);
		}else{
			sprintf(CONTENT_LENGTH, "CONTENT_LENGTH=%d", content_len);
			putenv(CONTENT_LENGTH);
		}

		dup2(input[0], 0);
		dup2(output[1], 1);

		execl(path, path, NULL);
		exit(1);
	}else{
		close(input[0]);
		close(output[1]);
		int i = 0;
		char c = '\0';
		for(; i < content_len; i++){
			recv(fd, &c, 1, 0);
			write(input[1], &c, 1);
		}
		while(1){
			ssize_t s = read(output[0], &c, 1);
			if(s > 0){
				send(fd, &c, 1, 0);
			}else{
				break;
			}
		}
		waitpid(id, NULL, 0);
		close(input[1]);
		close(output[0]);
	}

}

void *handler(void* arg)
{
	int fd = (int)arg;
	int error_code = 200;
	int cgi = 0;
	char *query_string = NULL;
#ifdef _DEBUG_
	printf("##########################################\n");
	char buff[SIZE];
	int ret = -1;

	while(ret < 0 && strcmp(buff, "\n") != 0){
		ret = get_line(fd, buff, sizeof(buff));
		printf("%s\n", buff);
	}

	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
#else
	char method[SIZE/10] = {0};
	char url[SIZE] = {0};
	char path[SIZE] = {0};
	char buff[SIZE] = {0};
	int len, i;
	if(get_line(fd, buff, sizeof(buff)) <= 0){
		goto end;
	}

	i = 0;len = 0;
	while(i < sizeof(method)-1 && len < sizeof(buff)\
			&& !isspace(buff[len])){
		method[i] = buff[len];
		len++;i++;
	}
	method[len] = 0;

	while(isspace(buff[len]) && len < sizeof(buff)){
		len++;
	}

	i=0;
	while(i < sizeof(url) && len < sizeof(buff)\
			&& !isspace(buff[len])){
		url[i] = buff[len];
		len++;i++;
	}
	url[len] = 0;

	//printf("method:%s, url:%s\n", method, url);
	if(strcasecmp(method, "get") && strcasecmp(method, "post")){
		print_log("method is not ok!", FATAL);
		error_code = 501;
		goto end;
	}

	if(strcasecmp(method, "post") == 0){
		cgi =1;
	}

	query_string = url;

	while(*query_string != 0){
		if(*query_string == '?'){
			cgi = 1;
			*query_string = '\0';
			query_string++;
			break;
		}
		query_string++;
	}
	sprintf(path, "wwwroot%s", url);
	if(path[strlen(path)-1] == '/'){
		strcat(path, "index.html");
	}

	printf("path:%s\n",path);

	struct stat st;
	if(stat(path, &st) < 0){
		print_log("path not found!", FATAL);
		error_code = 404;
		goto end;
	}else{
		if(S_ISDIR(st.st_mode)){
			strcat(path, "/index.html");
		}else{
			if((st.st_mode & S_IXGRP) ||\
					(st.st_mode & S_IXOTH) ||\
					(st.st_mode & S_IXUSR)){
				cgi = 1;
			}
		}

		if(cgi){
			exe_cgi(fd, method, path, query_string);
		}else{
			drop_header(fd);
			error_code = echo_www(fd, path, st.st_size);
		}
	}
#endif

end:
	echo_error(fd, error_code);
	close(fd);
}















