# **ThreadPool**

A simple thread pool implemented in C++11, and depends on the moodycamel::ConcurrentQueue library

# Usage samples

Basic usage

```C++
#include <iostream>
#include "ThreadPool.h"

int main()
{
    // create thread pool with 4 worker threads
    ThreadPool pool;

    //start pool
    pool.start();

    //dispatch one task
    pool.dispatchTask([]() { std::count<< "Hello World" << endl; });

    //stop threadpool
    pool.stop();
    
    return 0;
}

```
