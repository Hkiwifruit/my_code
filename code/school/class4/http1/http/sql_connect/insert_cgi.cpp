#include "sql_api.h"

using namespace std;

void insertToDb(const char* string_arg)
{
	
	char arg_buff[1024];
	strcpy(arg_buff, string_arg);
	char* myargv[6];
	char *start = arg_buff;
	int i = 0;
	while(*start){
		if(*start == '='){
			start++;
			myargv[i++] = start;
			//continue;
		}
		if(*start == '&'){
			*start = '\0';
		}
		start++;
	}

	sqlApi mydb("127.0.0.1", 3306);
	mydb.connect();
	mydb.insert(myargv[0],myargv[1],atoi(myargv[2]),myargv[3],myargv[4]);
	mydb.select();
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
			cout<<"content_len: "<<content_len<<endl;
			int i = 0;
			char c = '\0';
			for( ; i < content_len; i++){
				read(0, &c, 1);
				buf[i]=c;
				cout<<c<<endl;
			}
			buf[i] = '\0';
	}else{
	}

	insertToDb(string_arg);

	//mydb.insert("zhangsan","man",34,"coding","jiaoda");
	//mydb.select();
	return 0;
}
