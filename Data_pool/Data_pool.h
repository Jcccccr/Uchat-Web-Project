
#ifndef _DATA_POOL_H_
#define _DATA_POOL_H_

#include <stdio.h>
#include <vector>
#include <string>
#include <stdlib.h>
#include <semaphore.h>

using namespace std;

class data_pool
{
private:
     int cap;
	 int size;
	 int product_step;
	 int consumer_step;
	 sem_t blank;
	 sem_t data;
     vector<string>  pool;
private:
	 data_pool(const data_pool&);
public:
	 data_pool(int );
	 void getData(string& outString);
	 void putData(const string& inString);
	 ~data_pool();
};

#endif
