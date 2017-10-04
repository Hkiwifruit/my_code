#include "jsonApi.h"

jsonApi::jsonApi()
{
}

int jsonApi::serialize(Json::Value &val, std::string &outString)
{
#ifdef _Fast_
	Json::StyledWriter w;
	outString = w.write(val);
#else
	Json::FastWriter w;
	outString = w.write(val);
#endif
}
int jsonApi::deserialize(std::string &inString, Json::Value &val)
{
	Json::Reader r;
	if(r.parse(inString, val, false) < 0){
		return 0;
	}
	return 1;
}

jsonApi::~jsonApi()
{
}

//int main()
//{
//	jsonApi obj;
//	Json::Value v;
//	v["nick_name"] = "fly_fly";
//	v["school"] = "SUST";
//	v["msg"]= "hello world";
//	v["cmd"] = "Node";
//
//	std::string str;
//	obj.serialize(v,str);
//	std::cout<<str<<std::endl;
//	return 0;
//}
