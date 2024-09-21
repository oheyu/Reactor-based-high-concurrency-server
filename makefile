all: server client

server: epoll_server.cpp InetAddress.cpp
	g++ -o server epoll_server.cpp InetAddress.cpp

client: client.cpp
	g++ -o client client.cpp

clean:
	rm -f server
