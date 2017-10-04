#include "udpserver.h"
#include <unistd.h>

using namespace std;

static void usage(std::string proc)
{
	cout<<"Usage:  "<<proc<<" [local_ip] [local_port]"<<endl;
}

static void* runRecv(void *arg)
{
	udpServer *srvp = (udpServer*)arg;
	std::string msg;
	for(;;){
		srvp->recvData(msg);
		std::cout<<"client:"<<msg<<std::endl;
	}
	return (void*)0;
}

static void* runSend(void *arg)
{
	udpServer *srvp = (udpServer*)arg;
	for(;;){
		srvp->broadcast_msg();
	}
	return (void*)0;
}

int main(int argc, char* argv[])
{
	if(argc != 3){
		usage(argv[0]);
		exit(1);
	}
	int port = atoi(argv[2]);
	udpServer srv(argv[1], port);
	srv.init_server(port);

	daemon(0, 0);
	pthread_t recv_thread, send_thread;
	pthread_create(&recv_thread, NULL, runRecv, (void*)&srv);
	pthread_create(&send_thread, NULL, runSend, (void*)&srv);

	pthread_join(recv_thread, NULL);
	pthread_join(send_thread, NULL);

	return 0;
}
