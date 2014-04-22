#ifndef CONSUMER_H_
#define CONSUMER_H_
#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include "Thread.h"
#include "WorkingQueue.h"

class ConsumerThread:public Thread{
	public :
		ConsumerThread(WorkingQueue * p_queue) ;
		void run() ;
	private:
		WorkingQueue *_p_queue ;
};
#endif
