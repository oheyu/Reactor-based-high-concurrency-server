# Reactor-based-high-concurrency-server
This repository implements a high-concurrency server using the Reactor pattern, designed for efficient handling of multiple simultaneous I/O operations in a scalable and non-blocking manner. Ideal for applications requiring low-latency and high throughput.

## Step-1: Basic Tcp-Server based on Epoll
At the very first beginning, I just created a simple server based on epoll and optimize it immediately. To check it, I've created a client too.

## Step-2: Add InetAddress Class
Encapsulate the contents about 'sockaddr' to make things easy.

## Step-3: Add Socket Class
Encapsulate the contents like 'listen()', 'bind()' and 'setsockopt()'...

## Step-4: Add Epoll Class
Same as before, encapsulate contents about epoll this time.(By the way, I've refactored the whole structure for this project between Step-3 and Step-4)

## Step-5: Add Channel Class
Things are going to be complex.

## Step-5(1): Optimize Channel Class

## Step-6: Callback
The first time to try callback using 'std::function' and 'std::bind'.
