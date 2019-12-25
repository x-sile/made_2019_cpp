#pragma once

#include <queue>
#include <future>
#include <functional>

class ThreadPool {
public:
    explicit ThreadPool(size_t poolSize) {
        keep_working = true;

        for (size_t i = 0; i < poolSize; i++) {
            workers.emplace_back(
                    std::thread([this]() {
                        while (keep_working) {
                            std::unique_lock<std::mutex> lock(mutex_);
                            time_to_work.wait(lock, [this]() { return !tasks_queue.empty(); });

                            auto task = tasks_queue.front();
                            tasks_queue.pop();
                            lock.unlock();

                            task();
                        }
                    })
            );
        }
    }

    ThreadPool(const ThreadPool &copied) = delete;

    ThreadPool &operator=(const ThreadPool &copied) = delete;

    ThreadPool(ThreadPool &&moved) = delete;

    ThreadPool &operator=(ThreadPool &&moved) = delete;

    ~ThreadPool() {
        keep_working = false;
        time_to_work.notify_all();

        for (auto &worker: workers) {
            worker.join();
        }
    }

    template<class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))> {
        auto task = std::make_shared<std::packaged_task<decltype(func(args...))()>>(std::bind(func, args...));

        auto future = task->get_future();

        std::unique_lock<std::mutex> lock(mutex_);
        tasks_queue.emplace([task]() { (*task)(); });
        lock.unlock();
        time_to_work.notify_one();

        return future;
    }

private:
    std::atomic_bool keep_working;
    std::mutex mutex_;
    std::condition_variable time_to_work;
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks_queue;
};
