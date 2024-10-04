#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

#include "Epoll.h"
#include "Channel.h"
#include <functional>
#include <memory>
#include <unistd.h>
#include <sys/syscall.h>
#include <queue>
#include <mutex>
#include <sys/eventfd.h>

class Channel;
class Epoll;

class EventLoop {
private:
    std::unique_ptr<Epoll> epoll_;
    std::function<void(EventLoop*)> epoll_timeout_callback_;
    pid_t thread_id_;
    std::queue<std::function<void()>> task_queue_;
    std::mutex mutex_;
    int wakeup_fd_;
    std::unique_ptr<Channel> wakeup_channel_;

public:
    EventLoop();

    ~EventLoop();

    void run();

    void addChannel(Channel* channel);

    void removeChannel(Channel* channel);

    void setEpollTimeoutCallback(std::function<void(EventLoop*)> func);

    bool isInLoopThread();

    void queueInLoop(std::function<void()> fn); 

    void wakeup();

    void handleWakeup();
};

#endif
