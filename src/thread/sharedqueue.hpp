#ifndef __sharedqueue_hpp__
#define __sharedqueue_hpp__

#include <list>
#include <mutex>
#include <condition_variable>

template <typename T>
class SharedQueue {
    bool adding;
    std::mutex queue_mutex;
    std::condition_variable queue_cv;
    
    typedef typename std::list<T>::size_type size_type;
    std::list<T> queue;
    SharedQueue(const SharedQueue<T>& );

public:
    
    SharedQueue() : adding(true) {}
    ~SharedQueue() {}

    void add(const T& );
    T& subtract();
    size_type size();

    bool alive();
    void kill();
};


template<typename T>
void SharedQueue<T>::add(const T& item) {
    std::lock_guard<std::mutex> lockGuard(queue_mutex);

    if (!adding) return;
        
    queue.push_back(item);
        
    queue_cv.notify_one();
}


template<typename T>
T& SharedQueue<T>::subtract() {
    std::unique_lock<std::mutex> lockGuard(queue_mutex);
    queue_cv.wait(lockGuard, [this]{ return this->queue.size() > 0; });

    T& item = queue.front();
    queue.pop_front();

    return item;
}


template<typename T>
typename
SharedQueue<T>::size_type SharedQueue<T>::size() {
    std::lock_guard<std::mutex> lockGuard(queue_mutex);

    return queue.size();
}


template<typename T>
bool SharedQueue<T>::alive() {
    std::lock_guard<std::mutex> lockGuard(queue_mutex);

    return queue.size() != 0 || adding;
}

template<typename T>
void SharedQueue<T>::kill() {
    std::lock_guard<std::mutex> lockGuard(queue_mutex);

    adding = false;
}
#endif // __sharedqueue_hpp__
