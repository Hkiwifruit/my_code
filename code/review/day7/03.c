#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main( void )
{
    char buf[1024] = {};

    int flags;

    if ((flags=fcntl(0, F_GETFL)) == -1 )
        perror("fcntl get"),exit(1);
	
	 //   flags |= O_NONBLOCK;
		
	if ( fcntl(0, F_SETFL, flags) == -1 )
	        perror("fcntl set"),exit(1);


    if (read(0, buf, 1024)==-1)
		        perror("read"),exit(1);
	    printf("buf=%s\n", buf);
}
