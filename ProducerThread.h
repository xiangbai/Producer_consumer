#ifndef PRODUCERTHREAD_H_
#define PRODUCERTHREAD_H_
#include "Thread.h"
#include "WorkingQueue.h"
class ProducerThread:public Thread{
	public:
		ProducerThread(WorkingQueue *p_queue);
		void run() ;
	private:
		WorkingQueue *_p_queue ;
};
#endif

