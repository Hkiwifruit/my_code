#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<string.h>

void usage(const char *proc)
{
	printf("Usage: %s [local_ip] [local_prot]\n", proc);
}

int startup(const char *ip, int port)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0){
		perror("socket");
		exit(2);
	}

	printf("sock: %d\n", sock);
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);//主机转网络
	local.sin_addr.s_addr = inet_addr(ip);//先将点分十进制转换成四字节，再将四字节转网络地址

	if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0){//绑定
		perror("bind");
		exit(3);
	}
	
	if(listen(sock, 10) < 0){// 设置套接字为监听状态
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
	struct sockaddr_in client;
	while(1){
		socklen_t len = sizeof(client);
		int new_sock = accept(listen_sock, (struct sockaddr*)&client, &len);
		if(new_sock < 0){
			perror("accept");
			continue;
		}

		printf("get new client[%s:%d]\n", inet_ntoa(client.sin_addr),ntohs(client.sin_port));
	
		while(1){
			char buf[1024];
			ssize_t s = read(new_sock, buf, sizeof(buf)-1);
			if(s > 0){
				buf[s] = 0;
				printf("client# %s\n", buf);
				write(new_sock, buf, strlen(buf));
			}else if(s == 0){
				printf("client close!!!\n");
				break;
			}else{
				perror("read");
				break;
			}
		}
	}

	return 0;
}








