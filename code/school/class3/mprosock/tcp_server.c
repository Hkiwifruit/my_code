#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>

void usage(const char *proc)
{
	printf("Usage: %s [local_ip] [local_port]\n", proc);
}
int startup(char *ip, int port)
{

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0){
		perror("socket");
	//	return 2;
		exit(3);
	}

	printf("sock: %d\n", sock);

	struct sockaddr_in peer;
	peer.sin_family = AF_INET;
	peer.sin_port = htons(port);
	peer.sin_addr.s_addr = inet_addr(ip);

	if(bind(sock, (struct sockaddr*)&peer, sizeof(peer)) < 0){
		perror("bind");
	//	return 3;
		exit(3);
	}



	if(listen(sock, 10) < 0){
		perror("listen");
	//	return 4;
		exit(1);
	}

	return sock;
}


int main(int argc, char *argv[])
{

	if(argc != 3){
		usage(argv[0]);
		return 1;
	}

	int listen_sock=startup(argv[1], atoi(argv[2]));
	while(1){
		struct sockaddr_in client;
		socklen_t len = sizeof(client);
		int new_sock = accept(listen_sock, (struct sockaddr*)&client, &len);
		if(new_sock < 0){
			perror("accept");
			continue;
		}

		printf("get new client[%s:%d]\n",inet_ntoa(client.sin_addr), ntohs(client.sin_port));

		char buf[1024];
		pid_t id = fork();
		if(id < 0){
			perror("fork");
			close(new_sock);
			exit(1);
		}else if(id == 0){//child
			close(listen_sock);
			if(fork() > 0){
				exit(1);
			}
			while(1){
				ssize_t s = read(new_sock, buf, sizeof(buf)-1);
				if(s > 0){
					buf[s] = 0;
					printf("client# %s\n", buf);
					write(new_sock, buf, strlen(buf));
				}else if(s == 0){
					printf("client is quit!!!\n");
					exit(1);
				}else{
					perror("read");
					break;
				}
			}
			close(new_sock);
		}else{//father
			close(new_sock);
			waitpid(id, NULL, 0);
		}
	}

	return 0;
}
