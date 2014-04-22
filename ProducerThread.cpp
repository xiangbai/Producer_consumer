#include "ProducerThread.h"
#include <iostream>
#include <stdlib.h>
ProducerThread::ProducerThread(WorkingQueue *p_queue):_p_queue(p_queue)
{
	srand(1024);
}
void ProducerThread::run()
{
	while(true)
	{
		int tem = rand() %1024 ;
		std::cout<<"product a number : "<< tem <<std::endl;
		_p_queue->produce(tem);
		sleep(2);
	}
}
