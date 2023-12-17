#pragma once

#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>

template<typename T>
class safe_queue
{
private:
	mutable std::mutex mut;
	std::queue<T> data_queue;
	std::condition_variable data_cond;

public:
	safe_queue() {}

	safe_queue(safe_queue const& other)
	{
		std::lock_guard<std::mutex> lk(other.mut);
		data_queue = other.data_queue;
	}

	void push(T new_value)
	{
		std::lock_guard<std::mutex> lk(mut);
		data_queue.push(new_value);
		data_cond.notify_one();
	}

	bool pop(T& value)
	{
		std::lock_guard<std::mutex> lk(mut);
		if (data_queue.empty())
		{
			return false;
		}
		value = data_queue.front();
		data_queue.pop();
		return true;
	}

	std::shared_ptr<T> pop()
	{
		std::lock_guard<std::mutex> lk(mut);
		if (data_queue.empty())
		{
			return std::shared_ptr<T>();
		}
		std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
		data_queue.pop();
		return res;
	}

	bool empty() const
	{
		std::lock_guard<std::mutex> lk(mut);
		return data_queue.empty();
	}
};

