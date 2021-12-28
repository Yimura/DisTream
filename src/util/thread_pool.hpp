#pragma once
#include "common.hpp"

namespace distream
{
	class ThreadPool
	{
		std::atomic<bool> m_accept_jobs;
		std::condition_variable m_data_condition;

		std::stack<std::function<void()>> m_job_stack;
		std::mutex m_lock;

		uint32_t m_thread_limit;
		std::vector<std::thread> m_thread_pool;

		std::thread m_managing_thread;
	public:
		ThreadPool(uint32_t thread_limit = std::thread::hardware_concurrency());
		~ThreadPool();

		void destroy();
		void push(std::function<void()> func);
	private:
		void create();
		void done();
		void run();
	};

	inline ThreadPool* g_thread_pool{};
}