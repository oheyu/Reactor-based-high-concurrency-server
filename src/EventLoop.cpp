#include "EventLoop.h"

int createTimerFd(int seconds = 5) {
    int timer_fd {timerfd_create(CLOCK_MONOTONIC, TFD_CLOEXEC | TFD_NONBLOCK)};
    struct itimerspec timeout;
    memset(&timeout, 0, sizeof(struct itimerspec));
    timeout.it_value.tv_sec = seconds;
    timeout.it_value.tv_nsec = 0;
    timerfd_settime(timer_fd, 0, &timeout, 0);
    return timer_fd;
}

EventLoop::EventLoop(bool main_loop, int time_val, int timeout_val) 
    : epoll_(new Epoll), main_loop_(main_loop), wakeup_fd_(eventfd(0, EFD_NONBLOCK)), 
    wakeup_channel_(new Channel(this, wakeup_fd_)), timer_fd_(createTimerFd(time_val_)), 
    timer_channel_(new Channel(this, timer_fd_)), time_val_(time_val), timeout_val_(timeout_val) 
{
    wakeup_channel_->setReadCallback(std::bind(&EventLoop::handleWakeup, this));
    wakeup_channel_->enableReading();
    timer_channel_->setReadCallback(std::bind(&EventLoop::handleTimer, this));
    timer_channel_->enableReading();
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
    // printf("EventLoop::handleWakeup() thread is %ld.\n", syscall(SYS_gettid));
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

void EventLoop::handleTimer() {
    struct itimerspec timeout;
    memset(&timeout, 0, sizeof(struct itimerspec));
    timeout.it_value.tv_sec = time_val_;
    timeout.it_value.tv_nsec = 0;
    timerfd_settime(timer_fd_, 0, &timeout, 0);

    if (!main_loop_) {

    } else {
        time_t now {time(0)};
        for (const auto& conn : conns_) {
            if (conn.second->timeOut(now, timeout_val_)) {
                {
                    std::lock_guard<std::mutex> lock(another_mutex_);
                    conns_.erase(conn.first);
                }
                timer_callback_(conn.first);
            }
        }
    }
}

void EventLoop::addConnection(spConnection conn) {
    {
        std::lock_guard<std::mutex> lock(another_mutex_);
        conns_[conn->fd()] = conn;
    }
}

void EventLoop::setTimerCallback(std::function<void(int)> fn) {timer_callback_ = fn;}
