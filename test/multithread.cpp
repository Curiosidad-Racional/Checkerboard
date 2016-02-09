#include <iostream>
#include <thread>
#include <mutex>

#include "../src/thread/pointersstack.hpp"
#include "../src/thread/sharedqueue.hpp"
#include "../src/thread/multithread.hpp"


std::mutex cout_mutex;

void function_thread(SharedQueue<PointersStack<int>* >& queue) {
    std::thread::id tid = std::this_thread::get_id();

    while (queue.alive()) {
        {
            std::lock_guard<std::mutex> lockGuard(cout_mutex);
            PointersStack<int>* stack = queue.subtract();
            std::cout << tid
                      << " gets object: ";
            for (int i = 0; i < stack->size(); i++)
                std::cout << *(*stack)[i] << "  ";
            delete stack;
            std::cout << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}


int main(int argc, char *argv[])
{
    SharedQueue<PointersStack<int>* > queue;
    
    
    MultiThread mth;

    mth.create(function_thread, std::ref(queue));
    mth.create(function_thread, std::ref(queue));

    for (int i = 0; i < 10; i++) {
        queue.add(new PointersStack<int> (new int(i), new int(i*1000)));
    }
    queue.kill();


    {
        std::lock_guard<std::mutex> lockGuard(cout_mutex);
        std::cout << "Queue size: " << queue.size() << std::endl;
    }
    
    
    return 0;
}

