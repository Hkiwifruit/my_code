#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>

int main()
{
	struct winsize wz;

	while(1){
		ioctl(0, TIOCGWINSZ, &wz);
		printf("%d:%d\n", wz.ws_row, wz.ws_col);
		sleep(1);
	}
}
