#ifndef _UDP_SERVER_
#define _UDP_SERVER_



#define SIZE 1024

#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <vector>
#include <string>
#include <map>
//#include<pthread.h>
#include "Data_pool.h"

using namespace std;

class udpServer
{
private:
	int sock;
	int port;
	string ip;
	map<in_addr_t , struct sockaddr_in> user_List; //服务器维护的用户列表
    data_pool pool;
private:
	udpServer(const udpServer& udp);  //防拷贝措施
	
public:
    bool InitServer();
	udpServer(const string _ip , const int& _port); //构造
	const int RecvData(string& outString);
	const int SendData(const string &instring,\
			struct sockaddr_in &remote , socklen_t& len);
	void addUser(const struct sockaddr_in& remote);
	const int  broadcast();
    ~udpServer();
};

#endif
