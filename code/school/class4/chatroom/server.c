#define _GUN_SOURCE 1

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <poll.h>

#define USR_LIMIT 5
#define BUFFER_SIZE 64
#define FD_LIMIT 65535

struct client_data
{
	sockaddr_in address;
	char* write_buf;
	char buf[ BUFFER_SIZE ];
};

int setnonblocking( int fd )
{
	int old_option = fcntl( fd, F_GETFL );
	int new_option = old_option | O_NONBLOCK;
	fcntl( fd, F_SETFL, new_option );
	return old_option;
}

int main( int argc, char* argv[] )
{
	if( argc <=2 )
	{
		printf( " usage:\r\n %s [ip_addr] [port]\n\n", argc[0]);
		const char* ip = argv[1];
		int port = atoi( argv[2] );
		
		int ret = 0;
		struct sockaddr_in address;
		bzero( &address, sizeof( address ));
		address.sin_family = AF_INET;
		address.sin.s_addr = inet_pton( AF_INET, ip, &address);
		address.sin_port = htons( port );

		int listenfd = socket(PF_INET, SOCK_STREAM, 0);
		assert( listenfd >= 0 );

		ret = bind( listenfd, (struct sockaddr*)&address, sizeof(address) );
		assert( ret! = -1 );

		ret = listen( listenfd, 5);
		assert( ret != -1);

	}
}
