#ifndef SYNCHRONOUS_QUEUE_H
#define SYNCHRONOUS_QUEUE_H

#include <queue>
#include <mutex>

template <class T>
class SynchronousQueue {
private:
	std::queue<T> queue_;
public:
	SynchronousQueue() {}
	void add(T val) {
		//std::lock
	}
};

#endif // SYNCHRONOUS_QUEUE_H