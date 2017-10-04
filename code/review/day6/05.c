#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

int main()
{
	char c;
	char buf[1023] = {};
	struct termios ts;

	tcgetattr(0, &ts);
	ts.c_lflag &= ~(ICANON|ECHO);

	tcsetattr(0, TCSANOW, &ts);

	int i = 0;
	while(1){
		c = getchar();
		putchar('*');
		if(c == '\n')break;
		buf[i++] = c;
	}
	buf[i] = 0;
	printf("buf = %s\n", buf);
	ts.c_lflag |= (ICANON | ECHO);
	tcsetattr(0, TCSANOW, &ts);
}
