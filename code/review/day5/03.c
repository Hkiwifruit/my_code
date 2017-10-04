#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if(argc < 2){
		fprintf(stderr, "usage:%s file\n", argv[0]);
		exit(1);
	}

	FILE* fp = fopen(argv[1], "r");
	if(fp == NULL){
		fprintf(stderr, "open %s err\n", argv[1]);
		exit(2);
	}
	char c;
	while((c = fgetc(fp)) != EOF){
		fputc(c, stdout);
		fflush(stdout);
		usleep(100000);
	}
	fclose(fp);
}
