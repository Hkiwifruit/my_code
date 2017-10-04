#include <stdio.h>

int main( int argc, char *argv[], char *envp[])
{
    printf("argc=%d\n", argc);
	
	    printf("argv:\n");
		int i;
	    for ( i=0; i<argc; i++)
	        printf("\targv[%d]=%s\n", i, argv[i]);
			
	    printf("env:\n");
		for (i=0; envp[i]; i++)
			printf("\t%s\n", envp[i]);
}

