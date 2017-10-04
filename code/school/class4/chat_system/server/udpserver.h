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
#include "data_pool.h"
#include "log.h"
#include "dataType.h"

#define SIZE 1024

using namespace std;

class udpServer
{
	public:
		udpServer(const std::string &_ip, const int &_port);
		void init_server(int port);
		int recvData(std::string &outString);
		int sendData(const string &inString,\
				struct sockaddr_in &remote, socklen_t &len);
		int broadcast_msg();
		~udpServer();
	private:
		udpServer(const udpServer&);
		void delUser(const struct sockaddr_in &remote);
		void addUser(const struct sockaddr_in &remote);
	private:
		int sock;
		int port;
		std::string ip;
		data_pool pool;
		std::map<in_addr_t, struct sockaddr_in> user_List;
};

#endif
