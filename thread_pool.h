#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <queue>
#include <thread>
#include <future>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>

class ThreadPool {
public:
    explicit ThreadPool(size_t num_threads);
    ~ThreadPool();
    template<class F>
    auto enqueue(F&& f) -> std::future<decltype(f())>;
private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queue_mutex;
    std::condition_variable condition;
    std::atomic<bool> stop;
};
template<class F>
auto ThreadPool::enqueue(F&& f) -> std::future<decltype(f())> {
    using return_type = decltype(f());
    auto task = std::make_shared<std::packaged_task<return_type()>>(std::forward<F>(f));
    std::future<return_type> res = task->get_future();
    {
	std::unique_lock<std::mutex> lock(queue_mutex);
	tasks.emplace([task]() { (*task)(); });
    }
    condition.notify_one();
    return res;
}
#endif // THREAD_POOL_H
