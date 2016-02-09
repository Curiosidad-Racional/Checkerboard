#ifndef __multithread_hpp__
#define __multithread_hpp__

#include <vector>
#include <algorithm>
#include <thread>

class MultiThread {
    typedef std::vector<std::thread>::size_type size_type;
    std::vector<std::thread> workers;
public:
    MultiThread() {}

    ~MultiThread() {
        join();
    }
    
    template<typename Callable, typename... Args>
    void create(Callable&& f, Args&&... args);

    void join();
    void join(const size_type i);
    template<typename ...Args>
    void join(const size_type i, Args... args);

    void detach();
    void detach(const size_type i);
    template<typename ...Args>
    void detach(const size_type i, Args... args);
};


template<typename Callable, typename... Args>
void MultiThread::create(Callable&& f, Args&&... args) {
    workers.push_back(std::thread(f, args...));
}


void MultiThread::join() {
    std::for_each(workers.begin(), workers.end(), [](std::thread &th) {
            if (th.joinable()) th.join();
        });
}

void MultiThread::join(const size_type i) {
    if (workers[i].joinable()) workers[i].join();
}

template<typename ...Args>
void MultiThread::join(const size_type i, Args... args) {
    join(i);
    join(args...);
}


void MultiThread::detach() {
    std::for_each(workers.begin(), workers.end(), [](std::thread &th) {
            if (th.joinable()) th.detach();
        });
}

void MultiThread::detach(const size_type i) {
    if (workers[i].joinable()) workers[i].detach();
}

template<typename ...Args>
void MultiThread::detach(const size_type i, Args... args) {
    detach(i);
    detach(args...);
}

#endif // __multithread_hpp__
