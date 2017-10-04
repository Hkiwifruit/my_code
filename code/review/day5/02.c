#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char* argv[] = {"tst", "aa", "bb", "cc", NULL};
	char* env[] = {"PATH=usr/bin", "you=you", NULL};

	execve("tst", argv, env);
}
