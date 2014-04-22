#include "WorkingQueue.h"

WorkingQueue::WorkingQueue(std::queue<int>::size_type queue_size)
: _queue_size(queue_size) ,_queue() , _lock() , _empty(&_lock) , _full(&_lock)
{
	srand(10086) ;
}
WorkingQueue::~WorkingQueue(){
}
int WorkingQueue::consume()
{
	_lock.lock() ;
	int ret ;
	while(_queue.empty())
	{
		_full.wait();
	}
	ret = _queue.front() ;
	_queue.pop() ;
	_empty.notify() ;
	_lock.unlock() ;
	return ret ;
}
void WorkingQueue::produce(int num)
{
	_lock.lock() ;
	while(_queue.size() == _queue_size)
	{
		_empty.wait();
	}
	_queue.push(num);
	_full.notify() ;
	_lock.unlock() ;

}
