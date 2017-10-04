#include "log.h"

static std::string level[] = {
	"[NORMAL] ",
	"[NOTICE] ",
	"[WARNING] ",
	"[FATAL] ",
};

void print_log(std::string msg, int _level)
{
#ifdef DEBUG
	std::cout<<level[_level%4]<<msg<<std::endl;
#endif
}
