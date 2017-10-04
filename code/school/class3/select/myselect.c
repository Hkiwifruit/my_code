#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/select.h>


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

int fds[1024];

int main(int argc, char *argv[])
{
	if(argc != 3){
		usage(argv[0]);
	}

	int listen_sock = startup(argv[1], atoi(argv[2]));
	fd_set rfds;
	int nums = sizeof(fds)/sizeof(fds[0]);
	int i = 0;
	for(; i < 1024; i++){
		fds[i] = -1;
	}

	fds[0] = listen_sock;
	while(1){
		int maxfd = -1;
		struct timeval timeout = {0, 0};
		FD_ZERO(&rfds);
		for(i=0; i < nums; i++){
			if(fds[i] == -1){
				continue;
			}
			FD_SET(fds[i], &rfds);
			if(maxfd < fds[i]){
				maxfd = fds[i];
			}
		}

		switch(select(maxfd+1, &rfds, NULL, NULL, NULL))
		{
			case 0:
				perror("timeout");
				break;
			case -1:
				perror("select");
				//close()
				break;
			default:
				{
					for(i = 0; i < nums; i++){
						if(i == 0 && FD_ISSET(fds[i], &rfds)){
							struct sockaddr_in client;
							socklen_t len = sizeof(client);
							int new_sock = accept(listen_sock, (struct sockaddr*)&client, &len);
							printf("[%s:%d]\n",inet_ntoa(client.sin_addr), ntohs(client.sin_port));

							if(new_sock < 0){
								perror("accept");
								continue;
							}
							int j = 0;
							for(; j < nums; j++){
								if(fds[j] == -1){
									break;
								}
							}
							if(j == nums){
								close(new_sock);
							}else{
								fds[j] = new_sock;
							}
						}else if(i != 0 && FD_ISSET(fds[i], &rfds)){
							char buf[1024];
							ssize_t s = read(fds[i], buf, sizeof(buf)-1);
							if(s > 0){
								buf[s] = 0;
								printf("client say# %s\n", buf);
								write(fds[i], buf, strlen(buf));
							}else if(s == 0){
								printf("client quit!!!\n");
								close(fds[i]);
								fds[i] = -1;
							}else{
								perror("read");
								close(fds[i]);
								fds[i] = -1;
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
