# 生产者消费者

标签（空格分隔）： 项目描述 
---

##知识点

 - 多线程编程
 - 线程同步与互斥

##过程


> 封装一个工作队列类，使生产者和消费者都是在这个工作队列中工作，封装工厂类，以保证可有多个工作队列。

##类的设计

> noncopyable.h --->为了防止复制和赋值操作

```

#ifndef NONCOPYABLE_H_
#define NONCOPYABLE_H_
#include <iostream>
class noncopyable{
	protected:
		noncopyable(){
		}
		~noncopyable(){
		}
	private:
		noncopyable(const noncopyable &);
		noncopyable &operator=(const noncopyable &);
};
#endif

```

> MutexLock.h

```

#ifndef MUTEXLOCK_H_
#define MUTEXLOCK_H_
#include <iostream>
#include <pthread.h>
#include "noncopyable.h"

class Condition ;
class MutexLock:public noncopyable{
	friend class Condition ;
	private:
		pthread_mutex_t _mutex ;
	public:
		MutexLock();
		~MutexLock();
		void lock();
		void unlock();
};
#endif

```

> Condition.h

```
#ifndef CONDITION_H_
#define CONDITION_H_
#include <iostream>
#include <pthread.h>
#include "MutexLock.h"

class Condition:public noncopyable{
	private:
		pthread_cond_t _cond ;
		MutexLock *_p_mutex ;
	public:
		Condition(MutexLock *p_mutex);
		~Condition() ;
		void wait() ;
		void notify() ;
		void notifyAll() ;
};
#endif

```

> Thread.h

```
#ifndef THREAD_H_
#define THREAD_H_
#include <iostream>
#include <pthread.h>
class Thread{
	private:
		pthread_t _pth ;
	public:
		Thread() ;
		virtual ~Thread() ;
		void start() ;
		void join() ;
		static void *thread_handle(void *arg) ;
		virtual void run() = 0 ;
		pthread_t get_tid() const ;
};
#endif

```

> ConsumerThread.h

```
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

```

> ProducerThread.h

```
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

```

> WorkingQueue.h

```
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

```

> Factory.h

```
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

```

