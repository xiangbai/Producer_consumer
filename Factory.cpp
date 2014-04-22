#include "Factory.h"

Factory::Factory(std::size_t num_producer , std::size_t num_consumer ,	std::queue<int>::size_type size) :_size(size) , _queue(_size) , 
	_num_producer(num_producer),_num_consumer(num_consumer) ,
	_producers(_num_producer , ProducerThread(&_queue)),
	_consumers(_num_consumer , ConsumerThread(&_queue))
{

}
Factory::~Factory(){}

void Factory::start(){
	for (std::vector<ProducerThread>::iterator iter = _producers.begin();
			iter != _producers.end(); ++iter) {
		iter->start();
	}
	for (std::vector<ConsumerThread>::iterator iter = _consumers.begin();
			iter != _consumers.end(); ++iter) {
		iter->start();
	}

	for (std::vector<ProducerThread>::iterator iter = _producers.begin();
			iter != _producers.end(); ++iter) {
		iter->join();
	}
	for (std::vector<ConsumerThread>::iterator iter = _consumers.begin();
			iter != _consumers.end(); ++iter) {
		iter->join();
	}
}
