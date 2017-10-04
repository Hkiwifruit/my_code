#include<stdio.h>
#include<poll.h>
#include<errno.h>

int main()
{
	struct pollfd ev;
	ev.fd = 0;
	ev.events = POLLIN;
	ev.revents = 0;
	while(1){
		switch(poll(&ev, 1, -1))
		{
			case -1:
				perror("poll");
				break;
			case 0:
				printf("timeout!...");
				break;
			default:
				{
					if(ev.events & POLLIN){
						char buf[512];
						ssize_t s = read(ev.fd, buf, sizeof(buf));
						if(s > 0){
							buf[s-1] = 0;
							printf("stdin say# %s\n", buf);
						}else if(s == 0){

						}else{
							perror("read");
						}
					}

				}
				break;
		};
	}
	return 0;
}
