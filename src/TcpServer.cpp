#include "TcpServer.h"


TcpServer::TcpServer(const char* ip, uint16_t port, int num_threads) : num_threads_(num_threads) {
    main_loop_ = new EventLoop;
    main_loop_->setEpollTimeoutCallback(std::bind(&TcpServer::epollTimeout, this, std::placeholders::_1));

    acceptor_ = new Acceptor(main_loop_, ip, port);
    acceptor_->setNewConnection(std::bind(&TcpServer::newConnection, this, std::placeholders::_1));

    thread_pool_ = new ThreadPool(num_threads_, "IO");
    for (int i {0}; i < num_threads; ++i) {
        sub_loops_.push_back(new EventLoop);
        sub_loops_[i]->setEpollTimeoutCallback(std::bind(&TcpServer::epollTimeout, this, std::placeholders::_1));
        thread_pool_->addTask(std::bind(&EventLoop::run, sub_loops_[i]));
    }
}

TcpServer::~TcpServer() {
    delete acceptor_;
    delete main_loop_;
    for (auto& temp : connections_) delete temp.second;
}

void TcpServer::start() {main_loop_->run();}

void TcpServer::newConnection(Socket* client_socket) {
    Connection* conn {new Connection(sub_loops_[client_socket->fd() % num_threads_], client_socket)};

    conn->setCloseCallback(std::bind(&TcpServer::closeConnection, this, std::placeholders::_1));
    conn->setErrorCallback(std::bind(&TcpServer::errorConnection, this, std::placeholders::_1));
    conn->setProcessMessageCallback(std::bind(&TcpServer::processMessage, this, std::placeholders::_1, std::placeholders::_2));
    conn->setSendCompleteCallback(std::bind(&TcpServer::sendComplete, this, std::placeholders::_1));

    connections_[conn->fd()] = conn;

    if (new_connection_callback_) new_connection_callback_(conn);
}

void TcpServer::closeConnection(Connection* conn) {
    if (close_connection_callback_) close_connection_callback_(conn);
    connections_.erase(conn->fd());
    delete conn;
}

void TcpServer::errorConnection(Connection* conn) {
    if (error_connection_callback_) error_connection_callback_(conn);
    connections_.erase(conn->fd());
    delete conn;
}

void TcpServer::processMessage(Connection* conn, std::string& message) {
    if (process_message_callback_) process_message_callback_(conn, message);
}

void TcpServer::sendComplete(Connection* conn) {
    if (send_complete_callback_) send_complete_callback_(conn);
}

void TcpServer::epollTimeout(EventLoop* loop) {
    if (epoll_timeout_callback_) epoll_timeout_callback_(loop);
}

void TcpServer::setNewConnectionCallback(std::function<void(Connection*)> func) {
    new_connection_callback_ = func;
}

void TcpServer::setCloseConnectionCallback(std::function<void(Connection*)> func) {
    close_connection_callback_ = func;
}

void TcpServer::setErrorConnectionCallback(std::function<void(Connection*)> func) {
    error_connection_callback_ = func;
}

void TcpServer::setProcessMessageCallback(std::function<void(Connection*, std::string&)> func) {
    process_message_callback_ = func;
}

void TcpServer::setSendCompleteCallback(std::function<void(Connection*)> func) {
    send_complete_callback_ = func;
}

void TcpServer::setEpollTimeoutCallback(std::function<void(EventLoop*)> func) {
    epoll_timeout_callback_ = func;
}
