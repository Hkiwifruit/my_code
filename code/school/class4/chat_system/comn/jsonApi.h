#ifndef _JSONAPI_H_
#define _JSONAPI_H_

#include <iostream>
#include <string>
#include "json/json.h"

class jsonApi{
	public:
		jsonApi();
		static int serialize(Json::Value &val, std::string &outString);
		static int deserialize(std::string &inString, Json::Value &val);
		~jsonApi();

};

#endif
