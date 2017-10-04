#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void mymath(char* arg)
{
	printf("hello cgi\n");
	char* argv[6];
	int i = 0;
	char* start = arg;

	printf("%s\n",start);
	while(*start){
		if(*start == '='){
			start++;
			argv[i++] = start;
		}
		if(*start == '&'){
			*start = '\0';
		}
		start++;
	}
	printf("%s %s %s %s", argv[0], argv[1], argv[2], argv[3]);
	//printf("<html><h1>hello world </h1></html>");
}

int main()
{
	char* method = NULL;
	char* query_string = NULL;
	char* string_arg = NULL;
	int content_len = -1;
	char buf[1024];
	method = getenv("METHOD");
	printf("method))))))))))%s\n",method);
		
	if(method && strcasecmp(method, "GET") == 0){
		if(query_string = getenv("QUERY_STRING")){
			string_arg = query_string;
		}
	}else if(method && strcasecmp(method, "POST") == 0){
			content_len = atoi(getenv("CONTENT_LENGTH"));
			int i = 0;
			char c = '\0';
			for( ; i < content_len; i++){
				read(0, &c, 1);
				buf[i]=c;
			}
			buf[i] = '\0';
	}else{
		printf("get method error!\n");
		return 1;
	}
	mymath(string_arg);
	return 0;
}





















