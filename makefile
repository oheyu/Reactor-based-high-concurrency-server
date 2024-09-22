all: server client

server: epoll_server.cpp InetAddress.cpp Socket.cpp
	g++ -o server epoll_server.cpp InetAddress.cpp Socket.cpp

client: client.cpp
	g++ -o client client.cpp

clean:
	rm -f server
