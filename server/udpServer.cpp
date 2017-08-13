#include "udpServer.h"


udpServer::udpServer(const string _ip , const int& _port)
	:ip(_ip)
	,port(_port)     //在初始化列表里面没有给sock的初始化
	,pool(1024)
{
      //构造
}
bool udpServer:: InitServer()
{
	//创建套接字
   sock = socket(AF_INET , SOCK_DGRAM , 0);  //UDP
   if(sock < 0)
   {
	   exit(1);
   }

   struct sockaddr_in local;
   local.sin_family = AF_INET;
   local.sin_port = htons(port);
   local.sin_addr.s_addr = inet_addr(ip.c_str()); 

   if(bind(sock , (struct sockaddr*)&local , sizeof(local)) < 0)
   {
      //perror("bind");
 	  exit(2);
   }
   return true;
}  
//向用户表中添加信息
void udpServer:: addUser(const struct sockaddr_in& remote)
{
   user_List.insert(pair<in_addr_t ,\
		   struct sockaddr_in>(remote.sin_addr.s_addr ,remote));//为什么map的value值是套接字而不是其他的？
}

// 服务器接收数据 需要可靠性
const int udpServer::RecvData(string& outString)  //输出型参数
{
     char buf[SIZE];
     struct sockaddr_in remote;
	 socklen_t len = sizeof(remote);
	 ssize_t s = recvfrom(sock , buf , sizeof(buf) , 0 , \
			 (struct sockaddr*)&remote ,&len);

	if(s > 0)
	{
	   addUser(remote);     //在接收到客户端的数据后将对方放入map中
	   outString = buf;
	   pool.putData(outString);
	}
	return s;   //返回值是局部变量
}

//发送数据  同样需要可靠性
const int udpServer::SendData(const string &inString ,\
		struct sockaddr_in& remote , socklen_t& len)
{
    ssize_t s = sendto(sock , inString.c_str() , inString.size(),0,(struct sockaddr*)&remote , len);
	if(s < 0)
	{
	   exit(3);
	}
	return s;
}
//服务器发送数据是以广播的形式发送
const int udpServer:: broadcast()
{
	string msg;
    pool.getData(msg);  //msg  shuchu xing can shu 

	map<in_addr_t , struct sockaddr_in>:: iterator ite1 = user_List.begin();
	socklen_t len = 0;
	while(ite1 != user_List.end())
	{
	   len = sizeof(ite1->second);
       SendData(msg , ite1->second , len); //這里就是为什么value的值存放sock结构体
	   ite1++;
	}
}

//析构
udpServer::~udpServer()
{
  close(sock);
}

