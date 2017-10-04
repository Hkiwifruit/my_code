#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<poll.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/select.h>

#define SIZE 1024

static void usage(char* proc)
{
	printf("Usage :%s [local_ip] [local_port]\n",proc);
}

int startup(const char *ip, int port)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0){
		perror("socket");
		exit(1);
	}
	
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip);

	if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0){
		perror("bind");
		exit(2);
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
	}

	int listen_sock = startup(argv[1], atoi(argv[2]));
	struct pollfd ev[SIZE];
	memset(ev, 0, sizeof(ev));
	int nums = 0;
	ev[0].fd = listen_sock;
	ev[0].events = POLLIN;
	int count = 1;
	while(1){
		switch(nums = poll(ev, count, -1))
		{
			case -1:
				perror("poll");
				break;
			case 0:
				printf("timeout!...\n");
				break;
			default:
				{
					int i = 0;
					for(i=0; i < count; i++){
						if(i == 0 && (ev[i].revents & POLLIN )){
							struct sockaddr_in client;
							socklen_t len = sizeof(client);
							int client_sock = accept(listen_sock, (struct sockaddr*)&client, &len);
							if(client_sock < 0){
								perror("accept");
								continue;
							}
							else
							{
								printf("get a client \n");
								ev[count].fd = client_sock;
								ev[count].events = POLLIN;
								count++;
							}
							ev[i].revents = 0;
						}else if(ev[i].events & POLLIN){
							char buf[512];
							ssize_t s = read(ev[i].fd, buf, sizeof(buf)-1);
							if(s > 0){
								buf[s-1] = 0;
								printf("client say# %s\n", buf);
								write(ev[i].fd, buf, strlen(buf));
							}else if(s == 0){
								printf("client quit!!!\n");
								close(ev[i].fd);
								ev[i].fd=0;
								ev[i].events=0;
							}else{
								perror("read");
								close(ev[i].fd);
								ev[i].fd=0;
								ev[i].events=0;
							}
						}else{	}
					}
				}
				break;
		};
	}
//	fd_set rfds;
//	int nums = sizeof(fds)/sizeof(fds[0]);
//	int i = 0;
//	for(; i < 1024; i++){
//		fds[i] = -1;
//	}
//
//	fds[0] = listen_sock;
//	while(1){
//		int maxfd = -1;
//		struct timeval timeout = {0, 0};
//		FD_ZERO(&rfds);
//		for(i=0; i < nums; i++){
//			if(fds[i] == -1){
//				continue;
//			}
//			FD_SET(fds[i], &rfds);
//			if(maxfd < fds[i]){
//				maxfd = fds[i];
//			}
//		}
//
//		switch(select(maxfd+1, &rfds, NULL, NULL, NULL))
//		{
//			case 0:
//				perror("timeout");
//				break;
//			case -1:
//				perror("select");
//				//close()
//				break;
//			default:
//				{
//					for(i = 0; i < nums; i++){
//						if(i == 0 && FD_ISSET(fds[i], &rfds)){
//							struct sockaddr_in client;
//							socklen_t len = sizeof(client);
//							int new_sock = accept(listen_sock, (struct sockaddr*)&client, &len);
//							printf("[%s:%d]\n",inet_ntoa(client.sin_addr), ntohs(client.sin_port));
//
//							if(new_sock < 0){
//								perror("accept");
//								continue;
//							}
//							int j = 0;
//							for(; j < nums; j++){
//								if(fds[j] == -1){
//									break;
//								}
//							}
//							if(j == nums){
//								close(new_sock);
//							}else{
//								fds[j] = new_sock;
//							}
//						}else if(i != 0 && FD_ISSET(fds[i], &rfds)){
//							char buf[1024];
//							ssize_t s = read(fds[i], buf, sizeof(buf)-1);
//							if(s > 0){
//								buf[s] = 0;
//								printf("client say# %s\n", buf);
//								write(fds[i], buf, strlen(buf));
//							}else if(s == 0){
//								printf("client quit!!!\n");
//								close(fds[i]);
//								fds[i] = -1;
//							}else{
//								perror("read");
//								close(fds[i]);
//								fds[i] = -1;
//							}
//						}else{
//						}
//					}
//				}
//
//				break;
//		};
//	}

	return 0;
}
