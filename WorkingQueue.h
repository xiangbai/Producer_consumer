#ifndef WORKINGQUEUE_H_
#define WORKINGQUEUE_H_
#include <iostream>
#include <queue>
#include <stdlib.h>
#include "MutexLock.h"
#include "Condition.h"
class WorkingQueue:public noncopyable{
	private:
		std::queue<int>::size_type _queue_size ;
		std::queue<int> _queue ;
		MutexLock _lock ;
		Condition _empty ;
		Condition _full ;
	public:
		WorkingQueue(std::queue<int>::size_type queue_size) ;
		virtual ~WorkingQueue() ;
		int consume() ;
		void produce(int num);
};
#endif
