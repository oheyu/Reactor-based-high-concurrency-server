#include "ThreadPool.h"
#include <unistd.h>

ThreadPool::ThreadPool(size_t num_thread) : stop_(false) {
    for (size_t i {0}; i < num_thread; ++i) {
        threads_.emplace_back([this]{
            // std::cout << "Create thread: " << syscall(SYS_gettid) << std::endl;
            while (stop_ == false) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(this->mutex_);
                    this->condition_.wait(lock, [this]{
                        return ((this->stop_ == true) || (this->task_queue_.empty() == false));
                    });
                    if ((this->stop_ == true) && (this->task_queue_.empty() == true)) return;
                    task = std::move(this->task_queue_.front());
                    this->task_queue_.pop();
                    std::cout << "Thread is " << syscall(SYS_gettid) << std::endl;
                }
                task();
            }
        });
    }
}

void ThreadPool::addTask(std::function<void()> task) {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        task_queue_.push(task);
    }
    condition_.notify_one();
}

ThreadPool::~ThreadPool() {
    stop_ = true;
    condition_.notify_all();
    for (std::thread& thread : threads_) thread.join();
}
