#include "udpServer.h"
//#include <pthread.h>



static void* runRecv(void* arg)
{
   udpServer* svrp = (udpServer*)arg;
   string msg;
   for(;;)
   {
      svrp->RecvData(msg);
      cout << "client# " << msg << endl;
   }
}
static void* runSend(void* arg)
{
   udpServer* svrp = (udpServer*)arg;
   for(;;)
   {
      svrp->broadcast();
   }
}

int main(int argc ,char* argv[])
{

	int port = atoi(argv[2]);
	udpServer svr(argv[1] , port);
	svr.InitServer();
	pthread_t recv_thread;
	pthread_t send_thread;

	pthread_create(&recv_thread , NULL , runRecv , (void*)&svr);
	pthread_create(&send_thread , NULL , runSend , (void*)&svr);

	pthread_join(recv_thread , NULL);
	pthread_join(send_thread , NULL);

	return 0;
}
