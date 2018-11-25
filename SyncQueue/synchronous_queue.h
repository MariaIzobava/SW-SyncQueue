#ifndef SYNCHRONOUS_QUEUE_H
#define SYNCHRONOUS_QUEUE_H

#include <queue>
#include <mutex>

template <class T>
class SynchronousQueue {
private:
	std::queue<T> queue_;
	std::mutex mx_;
	std::condition_variable consumed_;
	std::condition_variable produced_;
	size_t max_size_;
public:
	SynchronousQueue(size_t max_size):max_size_(max_size) {}
	void produce(T val) {
		{
			std::unique_lock<std::mutex> lock(mx_);
			std::cout << val << " process came to ADD\n";
			produced_.wait(lock, [&]() { return queue_.size() != max_size_; } );
			//std::cout << val << " I'll ADD\n";
			queue_.push(val);
			std::cout << val << " was ADDED to the queue, there are " << queue_.size() << " elements in total\n";
		}
		consumed_.notify_one();
	}

	const  T& consume(int id) {
		T val;
		{
			std::unique_lock<std::mutex> lock(mx_);
			std::cout << id << " process came to ERASE\n";
			consumed_.wait(lock, [&]() {return queue_.size() != 0; });
			//std::cout << id << " I'll ERASE\n";
			val = queue_.front();
			queue_.pop();
			std::cout << val << " was ERASED from the queue by " << id << " process, there are " << queue_.size() << " elements in total\n";
		}
		produced_.notify_one();
		return val;
	}
};

#endif // SYNCHRONOUS_QUEUE_H