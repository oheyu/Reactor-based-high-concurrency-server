#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

#include "Epoll.h"
#include "Channel.h"
#include "Connection.h"
#include <functional>
#include <memory>
#include <unistd.h>
#include <sys/syscall.h>
#include <queue>
#include <map>
#include <atomic>
#include <mutex>
#include <sys/eventfd.h>
#include <sys/syscall.h>
#include <sys/timerfd.h>

class Channel;
class Epoll;
class Connection;

using spConnection = std::shared_ptr<Connection>;

class EventLoop {
private:
    int time_val_;
    int timeout_val_;
    std::unique_ptr<Epoll> epoll_;
    std::function<void(EventLoop*)> epoll_timeout_callback_;
    pid_t thread_id_;
    std::queue<std::function<void()>> task_queue_;
    std::mutex mutex_;
    int wakeup_fd_;
    std::unique_ptr<Channel> wakeup_channel_;
    int timer_fd_;
    std::unique_ptr<Channel> timer_channel_;
    bool main_loop_;
    std::map<int, spConnection> conns_;
    std::function<void(int)> timer_callback_;
    std::mutex another_mutex_;
    std::atomic_bool stop_;

public:
    EventLoop(bool main_loop, int time_val = 24, int timeout_val = 60);

    ~EventLoop();

    void run();

    void stop();

    void addChannel(Channel* channel);

    void removeChannel(Channel* channel);

    void setEpollTimeoutCallback(std::function<void(EventLoop*)> func);

    bool isInLoopThread();

    void queueInLoop(std::function<void()> fn); 

    void wakeup();

    void handleWakeup();

    void handleTimer();

    void addConnection(spConnection conn);

    void setTimerCallback(std::function<void(int)> fn);
};

#endif
