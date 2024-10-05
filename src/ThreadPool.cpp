#include "ThreadPool.h"
#include <unistd.h>

ThreadPool::ThreadPool(size_t num_thread, const std::string& thread_type) : stop_(false), thread_type_(thread_type) {
    for (size_t i {0}; i < num_thread; ++i) {
        threads_.emplace_back([this]{
            printf("Create %s thread (%ld).\n", thread_type_.c_str(), syscall(SYS_gettid));
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
                }
                // printf("%s (%ld) execute task.\n", thread_type_.c_str(), syscall(SYS_gettid));
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

size_t ThreadPool::size() const {
    return threads_.size();
}
