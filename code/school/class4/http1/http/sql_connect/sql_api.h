#ifndef _SQL_
#define _SQL_

#include <iostream>
#include <string>
#include <mysql.h>
#include <string.h>
#include <stdlib.h>

class sqlApi{
	public:
		sqlApi(const std::string &_h,\
				const int &_port,\
				const std::string &_u="root",\
				const std::string &_p="123456",\
				const std::string &_db="Linux_4");
		int connect();
		int insert(const std::string &_name,\
				   const std::string &_sex,\
				   const int &_age,\
				   const std::string &_hobby,\
				   const std::string &_school);
		int select();
		~sqlApi();
	private:
		MYSQL* conn;
		std::string host;
		std::string user;
		std::string passwd;
		std::string db;
		int port;
};


#endif
