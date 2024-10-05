#include "TcpServer.h"


TcpServer::TcpServer(const char* ip, uint16_t port, int num_threads) : num_threads_(num_threads) {
    main_loop_ = new EventLoop(true);
    main_loop_->setEpollTimeoutCallback(std::bind(&TcpServer::epollTimeout, this, std::placeholders::_1));

    acceptor_ = new Acceptor(main_loop_, ip, port);
    acceptor_->setNewConnection(std::bind(&TcpServer::newConnection, this, std::placeholders::_1));

    thread_pool_ = new ThreadPool(num_threads_, "IO");
    for (int i {0}; i < num_threads; ++i) {
        sub_loops_.push_back(new EventLoop(false));
        sub_loops_[i]->setEpollTimeoutCallback(std::bind(&TcpServer::epollTimeout, this, std::placeholders::_1));
        sub_loops_[i]->setTimerCallback(std::bind(&TcpServer::removeConn, this, std::placeholders::_1));
        thread_pool_->addTask(std::bind(&EventLoop::run, sub_loops_[i]));
    }
}

TcpServer::~TcpServer() {
    delete acceptor_;
    delete main_loop_;
    for (auto& temp : sub_loops_) delete temp;
    delete thread_pool_;
}

void TcpServer::start() {main_loop_->run();}

void TcpServer::serverStop() {
    main_loop_->stop();
    printf("Main loop is stopped.\n");
    for (int i {0}; i < num_threads_; ++i) {sub_loops_[i]->stop();}
    printf("Sub loop is stopped.\n");
    thread_pool_->stop();
    printf("IO thread is stopped.\n");
}

void TcpServer::newConnection(Socket* client_socket) {
    spConnection conn(new Connection(sub_loops_[client_socket->fd() % num_threads_], client_socket));

    conn->setCloseCallback(std::bind(&TcpServer::closeConnection, this, std::placeholders::_1));
    conn->setErrorCallback(std::bind(&TcpServer::errorConnection, this, std::placeholders::_1));
    conn->setProcessMessageCallback(std::bind(&TcpServer::processMessage, this, std::placeholders::_1, std::placeholders::_2));
    conn->setSendCompleteCallback(std::bind(&TcpServer::sendComplete, this, std::placeholders::_1));

    {
        std::lock_guard<std::mutex> lock(mutex_);
        connections_[conn->fd()] = conn;
    }
    sub_loops_[client_socket->fd() % num_threads_]->addConnection(conn);

    if (new_connection_callback_) new_connection_callback_(conn);
}

void TcpServer::closeConnection(spConnection conn) {
    if (close_connection_callback_) close_connection_callback_(conn);
    {
        std::lock_guard<std::mutex> lock(mutex_);
        connections_.erase(conn->fd());
    }
}

void TcpServer::errorConnection(spConnection conn) {
    if (error_connection_callback_) error_connection_callback_(conn);
    {
        std::lock_guard<std::mutex> lock(mutex_);
        connections_.erase(conn->fd());
    }
}

void TcpServer::processMessage(spConnection conn, std::string& message) {
    if (process_message_callback_) process_message_callback_(conn, message);
}

void TcpServer::sendComplete(spConnection conn) {
    if (send_complete_callback_) send_complete_callback_(conn);
}

void TcpServer::epollTimeout(EventLoop* loop) {
    if (epoll_timeout_callback_) epoll_timeout_callback_(loop);
}

void TcpServer::setNewConnectionCallback(std::function<void(spConnection)> func) {
    new_connection_callback_ = func;
}

void TcpServer::setCloseConnectionCallback(std::function<void(spConnection)> func) {
    close_connection_callback_ = func;
}

void TcpServer::setErrorConnectionCallback(std::function<void(spConnection)> func) {
    error_connection_callback_ = func;
}

void TcpServer::setProcessMessageCallback(std::function<void(spConnection, std::string&)> func) {
    process_message_callback_ = func;
}

void TcpServer::setSendCompleteCallback(std::function<void(spConnection)> func) {
    send_complete_callback_ = func;
}

void TcpServer::setEpollTimeoutCallback(std::function<void(EventLoop*)> func) {
    epoll_timeout_callback_ = func;
}

void TcpServer::removeConn(int fd) {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        connections_.erase(fd);
    }
}
