#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "datecalc.h"
#include "datecalc.cpp"

void calc(char* arg)
{
	char* argv[6];
	int i = 0;
	char* start = arg;
	
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

	int year1 = atoi(argv[0]);
	int month1 = atoi(argv[1]);
	int day1 = atoi(argv[2]);

	int year2 = atoi(argv[3]);
	int month2 = atoi(argv[4]);
	int day2 = atoi(argv[5]);


	datecalc d1(year1, month1, day1);
	datecalc d2(year2, month2, day2);
	cout<<"Days is: "<<d1-d2<<"<br>"<<endl;
}

int main()
{
	char* method = NULL;
	char* query_string = NULL;
	char* string_arg = NULL;
	int content_len = -1;
	char buf[1024];
	method = getenv("METHOD");
		
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
	calc(string_arg);
	return 0;
}





















