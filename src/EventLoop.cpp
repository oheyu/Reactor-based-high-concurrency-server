#include "EventLoop.h"

EventLoop::EventLoop() 
    : epoll_(new Epoll), wakeup_fd_(eventfd(0, EFD_NONBLOCK)), wakeup_channel_(new Channel(this, wakeup_fd_)) {
    wakeup_channel_->setReadCallback(std::bind(&EventLoop::handleWakeup, this));
    wakeup_channel_->enableReading();
}

EventLoop::~EventLoop() {}

void EventLoop::run() {
    thread_id_ = syscall(SYS_gettid);
    while (true) {
        std::vector<Channel*> results {epoll_->loop()};
        if (results.size() == 0) epoll_timeout_callback_(this);
        for (auto& result : results) {result->handleEvent();}
    }
}

void EventLoop::addChannel(Channel* channel) {
    epoll_->addChannel(channel);
}

void EventLoop::removeChannel(Channel* channel) {
    epoll_->removeChannel(channel);
}

void EventLoop::setEpollTimeoutCallback(std::function<void(EventLoop*)> func) {
    epoll_timeout_callback_ = func;
}

bool EventLoop::isInLoopThread() {
    return thread_id_ == syscall(SYS_gettid);
}

void EventLoop::queueInLoop(std::function<void()> fn) {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        task_queue_.push(fn);
    }
    wakeup();
}

void EventLoop::wakeup() {
    uint64_t val {1};
    ::write(wakeup_fd_, &val, sizeof(val));
}

void EventLoop::handleWakeup() {
    printf("EventLoop::handleWakeup() thread is %ld.\n", syscall(SYS_gettid));
    uint64_t val {1};
    ::read(wakeup_fd_, &val, sizeof(val));

    std::function<void()> fn;
    std::lock_guard<std::mutex> lock(mutex_);
    while(!task_queue_.empty()) {
        fn = std::move(task_queue_.front());
        task_queue_.pop();
        fn();
    }
}
