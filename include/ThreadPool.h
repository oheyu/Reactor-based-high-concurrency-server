#ifndef THTREAD_POOL_H
#define THTREAD_POOL_H

#include <iostream>
#include <cstdio>
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
    std::string thread_type_;

public:
    ThreadPool(size_t num_thread, const std::string& thread_type);

    void addTask(std::function<void()> task);

    size_t size() const;

    void stop();

    ~ThreadPool();
};

#endif // !THTREAD_POOL_H
