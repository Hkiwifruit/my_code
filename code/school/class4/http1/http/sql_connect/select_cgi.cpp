#include "sql_api.h"

using namespace std;

void selectFromDb(const char* string_arg)
{
	sqlApi mydb("127.0.0.1", 3306);
	mydb.connect();
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
			int i = 0;
			char c = '\0';
			for( ; i < content_len; i++){
				read(0, &c, 1);
				buf[i]=c;
			}
			buf[i] = '\0';
	}else{
	}

	selectFromDb(string_arg);

	//mydb.insert("zhangsan","man",34,"coding","jiaoda");
	//mydb.select();
	return 0;
}
