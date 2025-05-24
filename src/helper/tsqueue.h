#ifndef TSQUEUE_CLASS_H
#define TSQUEUE_CLASS_H
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>

template <typename T>
class tsQueue {
private:
	std::queue<T> _queue;
	std::mutex _mutex;
	std::condition_variable _cond;
public:
	void push(T task) {
		std::unique_lock<std::mutex> lock(_mutex);
		_queue.push(task);
		_cond.notify_one();
	}
	T pop() {
		std::unique_lock<std::mutex> lock(_mutex);
		// jeżeli puste, to powinno być OK?
		T task = _queue.front();
		_queue.pop();
		return task;
	}
	bool empty() {
		std::unique_lock<std::mutex> lock(_mutex);
		return _queue.empty();
	}
};

extern tsQueue<std::function<void()>> terrainGenQueue;

#endif // TSQUEUE_CLASS_H