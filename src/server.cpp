#include <iostream>
#include <string>
#include <mutex>

#include "tcp/acceptor.hpp"
#include "thread/pointersstack.hpp"
#include "thread/sharedqueue.hpp"
#include "thread/multithread.hpp"


#define PORT 12321
#define MSG_SIZE 64



std::mutex cout_mutex;

void function_thread(SharedQueue<PointersStack<Stream>* >& queue) {
    std::thread::id tid = std::this_thread::get_id();

    PointersStack<Stream>* stack;
    Stream* stream0, *stream1;
    
    while (queue.alive()) {
        {
            std::lock_guard<std::mutex> lockGuard(cout_mutex);
            std::cout << "Thread " << tid << " starting game" << std::endl;
        }
        
        stack = queue.subtract();

        stream0 = (*stack)[0];
        stream1 = (*stack)[1];

        // initial state
        stream0->send("whte");
        stream1->send("blck");

        // communication between clients
        std::string msg;
        for (;;) {
            msg = stream0->recv(MSG_SIZE);
            if (msg.length() < 1) break; // end of stream
            {
                std::lock_guard<std::mutex> lockGuard(cout_mutex);
                std::cout << "Thread " << tid << " white -> black";
                for (int i = 0; i < msg.length(); ++i)
                    std::cout << " " << (int)msg[i];
                std::cout << std::endl;
            }
            stream1->send(msg);

            msg = stream1->recv(MSG_SIZE);
            if (msg.length() < 1) break; // end of stream
            {
                std::lock_guard<std::mutex> lockGuard(cout_mutex);
                std::cout << "Thread " << tid << " black -> white";
                for (int i = 0; i < msg.length(); ++i)
                    std::cout << " " << (int)msg[i];
                std::cout << std::endl;
            }
            stream0->send(msg);
        }
        
        delete stack;
    }
}



int main(int argc, char** argv)
{
    // command arguments
    if ( argc < 2 || 3 < argc ) {
        std::cerr << "usage: " << argv[0] << " <games> [<port>]" << std::endl;
        return -1;
    }

    // games threads
    unsigned int games = std::stoi(argv[1]);

      // common queue
    SharedQueue<PointersStack<Stream>* > queue;

    MultiThread mth;

    for (unsigned int i = 0; i < games; ++i)
        mth.create(function_thread, std::ref(queue));
    

    
    // acceptor
    unsigned int port;
    if (argc == 3)
        port = std::stoi(argv[2]);
    else
        port = PORT;

    
    Acceptor acceptor(port);

    if (acceptor.start() != 0) {
        std::cerr << "error: starting acceptor" << std::endl;
        return -1;
    }

    // main loop
    for (;;) {

        Stream* connection0;
        do {
            connection0 = acceptor.accept();
        } while (connection0 == NULL);
        std::cout << "Connection 1 of 2 accepted" << std::endl;

        Stream* connection1;
        do {
            connection1 = acceptor.accept();
        } while (connection1 == NULL);
        std::cout << "Connection 2 of 2 accepted" << std::endl;

        queue.add(new PointersStack<Stream> (connection0, connection1));
        
    }


    return 0;
}
