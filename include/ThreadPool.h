#ifndef THTREAD_POOL_H
#define THTREAD_POOL_H

#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <sys/syscall.h>
#include <unistd.h>
#include <utility>

class ThreadPool {
private:
    std::vector<std::thread> threads_;
    std::queue<std::function<void()>> task_queue_;
    std::mutex mutex_;
    std::condition_variable condition_;
    std::atomic_bool stop_;

public:
    ThreadPool(size_t num_thread);

    void addTask(std::function<void()> task);

    ~ThreadPool();
};

#endif // !THTREAD_POOL_H
