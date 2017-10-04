#define _GNU_SOURCE 1
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <poll.h>
#include <fcntl.h>

#define BUFFER_SIZE 64

int main( int argc, char* argv[] )
{
	if(argc <= 2){
		printf("usage: \r\t %s [local_ip] [local_port]");
		return 1;
	}
	const char* ip = argv[1];
	int port = atoi( argv[2] );

	struct sockaddr_in server_addr;
	bzero( &server_addr, sizeof( server_addr ));
	server_addr.sin_family = AF_INET;
	inet_pton( AF_INET, ip, &server_addr.sin_addr );
	server_addr.sin_port = htons( port );

	int sock = socket( AF_INET, SOCK_STREAM, 0);
	assert( sock >= 0 );
	if( connect( sock, (struct sockaddr*)&server_addr, sizeof( server_addr ) < 0)){
		perror("connect");
		close(sock);
		return 2;
	}

	struct pollfd fd[2];
	fd[0].fd = 0;
	fd[0].events = POLLIN;
	fd[0].revents = 0;
	fd[1].fd = sock;
	fd[1].events = POLLIN | POLLHUP;
	fd[1].revents = 0;

	char read_buf[BUFFER_SIZE];
	int pipefd[2];
	int ret = pipe( pipefd );
	assert( ret != -1 );

	while(1){
		ret = poll( fd, 2, -1 );
		if( ret < 0 ){
			printf("poll failure\n");
			break;
		}

		if( fd[1].revents & POLLHUP ){
			printf( "server close the connection\n" );
			break;
		}else if( fd[1].revents & POLLIN ){
			memset( read_buf, '\0', BUFFER_SIZE );
			recv( fd[1].fd, read_buf, BUFFER_SIZE-1, 0);
			printf( "%s\n", read_buf );
		}

		if( fd[0].revents & POLLIN ){
			ret = splice( 0, NULL, pipefd[1], NULL,\
					32768, SPLICE_F_MORE | SPLICE_F_MOVE);
			ret = splice( pipefd[0], NULL, sock, NULL,32768,\
					SPLICE_F_MORE | SPLICE_F_MOVE);
		}
	}

	close( sock );
	return 0;
}
