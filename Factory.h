#ifndef FACTORY_H_
#define FACTORY_H_
#include <vector>
#include <queue>
#include "WorkingQueue.h"
#include "ConsumerThread.h"
#include "ProducerThread.h"
class Factory{
	private:
		std::queue<int>::size_type _size ;
		WorkingQueue _queue ;
		std::size_t _num_producer ;
		std::size_t _num_consumer ;
		std::vector<ProducerThread> _producers ;
		std::vector<ConsumerThread> _consumers ;
	public:
		Factory(std::size_t num_producer , std::size_t num_consumer ,	std::queue<int>::size_type size) ;
		void start() ;
		~Factory();
};
#endif
