#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/epoll.h>
#include<string.h>


#define SIZE 64
char *msg1 = "HTTP/1.0 200 OK\r\n\r\n<html><h2>hello epoll!</h1></html>";
char *msg2 = "<html><h1><meta http-equiv=Content-Type content=text/html; charset=UTF-8/><title> 我的第一个 </title></head><body> <p>这是我的第一个网页,<a href=http://www.aaabbb.com/xhtml/> 尽情学习HTML吧!</a>吧!</p></body></html>";

static void usage(const char *proc)
{
	printf("Usage: %s [local_ip] [local_port]\n", proc);
}

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

	if(listen(sock, 10) < 0){
		perror("listen");
		exit(4);
	}

	return sock;
}

int main(int argc, char *argv[])
{
	if(argc != 3){
		usage(argv[0]);
		return 1;
	}

	int listen_sock = startup(argv[1], atoi(argv[2]));
	int epfd = epoll_create(256);
	if(epfd < 0){
		perror("epoll_create");
		close(listen_sock);
		return 5;
	}

	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.fd = listen_sock;

	epoll_ctl(epfd, EPOLL_CTL_ADD, listen_sock, &ev);


	int nums = 0;
	int timeout = -1;
	struct epoll_event revs[SIZE];
	while(1)
	{
		switch(nums = epoll_wait(epfd, revs, SIZE, timeout))
		{
			case -1:
				perror("epoll_wait");
				break;
			case 0:
				printf("timeout!...\n");
				break;
			default:
			{
				int i = 0;
				for(; i < nums; i++){
					int sock = revs[i].data.fd;
					if(sock == listen_sock && (revs[i].data.fd & EPOLLIN)){// listen_sock ready
						struct sockaddr_in client;
						socklen_t len = sizeof(client);
						int new_sock = accept(sock, (struct sockaddr*)&client, &len);
						if(new_sock < 0){
							perror("accept");
							continue;
						}

						printf("get a new accept [%s:%d]\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

						ev.data.fd = new_sock;
						ev.events = EPOLLIN;
						epoll_ctl(epfd, EPOLL_CTL_ADD, new_sock, &ev);

					}else if(sock != listen_sock){//
						if(revs[i].events & EPOLLIN){
							char buf[1024];
							ssize_t s = read(sock, buf, sizeof(buf));
							if(s > 0){
								buf[s-1] = 0;
								printf("client# %s\n", buf);

								ev.events = EPOLLOUT;
								ev.data.fd = sock;
								epoll_ctl(epfd, EPOLL_CTL_MOD, sock, &ev);
							}else if(s == 0){
								close(sock);
								epoll_ctl(epfd, EPOLL_CTL_DEL, sock, NULL);
								printf("client is quit!...\n");
							}else{
								close(sock);
								epoll_ctl(epfd, EPOLL_CTL_DEL, sock, NULL);
								perror("read");
							}
						}else if(revs[i].events & EPOLLOUT){
							write(sock, msg1, strlen(msg1));

							close(sock);
							epoll_ctl(epfd, EPOLL_CTL_DEL, sock, NULL);
						}
					}else{
					}
				}
			}
				break;
		};
	}


	return 0;
}
