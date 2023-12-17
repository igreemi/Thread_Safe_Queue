#pragma once
#include <vector>
#include <thread>
#include <functional>
#include "safe_queue.h"
#include "join_threads.h"

class thread_pool
{
private:
	std::atomic_bool done;
	safe_queue<std::function<void()>> work_queue;
	std::vector<std::thread> threads;
	join_threads joiner;

	void worker_thread();

public:

	thread_pool();

	~thread_pool();

	template<typename FunctionType>
	void submit(FunctionType f)
	{
		work_queue.push(std::function<void()>(f));
	}
};

