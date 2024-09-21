# Reactor-based-high-concurrency-server
This repository implements a high-concurrency server using the Reactor pattern, designed for efficient handling of multiple simultaneous I/O operations in a scalable and non-blocking manner. Ideal for applications requiring low-latency and high throughput.

## Step-1: Basic Tcp-Server based on Epoll
At the very first beginning, I just created a simple server based on epoll and optimize it immediately. To check it, I've created a client too.

## Step-2: Add InetAddress Class
Encapsulate the contents about 'sockaddr' to make things easy.
