## Reactor-based-high-concurrency-server
This repository implements a high-concurrency server using the Reactor pattern, designed for efficient handling of multiple simultaneous I/O operations in a scalable and non-blocking manner. Ideal for applications requiring low-latency and high throughput.

### Step-1: Basic Tcp-Server based on Epoll
At the very first beginning, I just created a simple server based on epoll and optimize it immediately. To check it, I've created a client too.

### Step-2: Add InetAddress Class
Encapsulate the contents about 'sockaddr' to make things easy.

### Step-3: Add Socket Class
Encapsulate the contents like 'listen()', 'bind()' and 'setsockopt()'...

### Step-4: Add Epoll Class
Same as before, encapsulate contents about epoll this time.(By the way, I've refactored the whole structure for this project between Step-3 and Step-4)

### Step-5: Add Channel Class
Things are going to be complex.

### Step-5(1): Optimize Channel Class

### Step-6: Callback
The first time to try callback using 'std::function' and 'std::bind'.

### Step-7: Add EventLoop Class
I don't know what to say. Just for encapsulation.

### Step-7(1): Optimize EventLoop Class
Just remember that the relationship between EventLoop and Channel is one-to-one.

### Step-8: Add TcpServer Class
The more higher abstraction.

### Step-9: Add Acceptor Class
Abstract connection process in TcpServer.

### Step-10: Add Connection Class
The same as Acceptor.

### Step-11: Optimize callback function
Try to figure out the relationship beween different modules if you want to write various class correctly.

### Step-12: Optimize again
Mainly optimize whole strcuture concerning about 'Channel', 'Connection' and 'tcpserver'.

### Step-13: Add Buffer Class.
Buffer is very important.

### Step-14: How to use Buffer in Connection.
We should know that the buffer we defined here is between buffer in kernel space (TCP Buffer, more precisedly) and applications in user space.
 
### Step-15: Optimize callback function again.
Giving message back to TcpServer when epoll timeout.

### Step-16: Abstract all things into higher level.
Adding "EchoServer" on "TcpServer".

### Step-17: Add ThreadPool Class.
Nothing to show here, a little bit simple.

### Step-18: Adjust to multi-thread.

### Step-19: Add Work Thread.

### Step-20: Optimize with smart pointer.
This step, mostly for life of object. I've used shared-ptr and unique-ptr. But the latter caused default, and I have no idea to solve it.

### Step-21: Asynchronous Event Loop Wake-up.
Here, the worker thread passes the process of handling the information to the event loop through the queue, and wakes up the event loop to execute the steps for processing the information.

### Step-22: Clean Connection in idle.

### Step-23: Exit with peace.
