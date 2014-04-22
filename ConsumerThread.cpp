#include "ConsumerThread.h"

ConsumerThread::ConsumerThread(WorkingQueue * p_queue):_p_queue(p_queue)
{
}
void ConsumerThread::run()
{
	while(true)
	{
		int tmp ;
		tmp = _p_queue->consume();
		std::cout<<"consume a number : "<<tmp<<std::endl;
		sleep(1);
	}
}
