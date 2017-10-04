#ifndef _UDPSERVER_H_
#define _UDPSERVER_H_

#include <iostream>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <string>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include "log.h"
#include <vector>
#include <algorithm>


#define SIZE 1024

using namespace std;

class udpClient
{
	public:
		udpClient(const std::string &_srv_ip, const int &_srv_port);
		void initClient(int port);
		int recvData(std::string &outString);
		int sendData(const string &inString);
		void addUser(std::string &_friend);
		void delUser(std::string &_friend);
		~udpClient();

		std::vector<std::string>flist;
	private:
		udpClient(const udpClient&);
	private:
		int sock;
		int server_port;
		std::string server_ip;
	//	struct sockaddr_in server;
	//	std::map<in_addr_t, struct sockaddr_in> user_List;
};

#endif
