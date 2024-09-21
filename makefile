all: server client

server: epoll_server.cpp
	g++ -o server epoll_server.cpp

client: client.cpp
	g++ -o client client.cpp

clean:
	rm -f server
