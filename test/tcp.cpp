#include <iostream>
#include <thread>
#include <string>
#include <mutex>

#include "../src/tcp/stream.hpp"
#include "../src/tcp/connector.hpp"
#include "../src/tcp/acceptor.hpp"

#define READ_BUFFER_SIZE 16

std::mutex cout_mutex;

void client() {
    Connector connector;

    Stream* stream = connector.connect(1234);

    if (stream) {
        stream->send({ 4, 3, 2, 1, -1, -2, -3, -4 });
        std::string msg = stream->recv(READ_BUFFER_SIZE);
        {
            std::lock_guard<std::mutex> guard(cout_mutex);
            std::cout << "client recieve:";
            for (int i = 0; i < msg.length(); ++i)
                std::cout << " " << (int)msg[i];
            std::cout << std::endl;
        }
        
        delete stream;
    }
    
}

int main(int argc, char *argv[])
{
    Acceptor acceptor(1234);

    if (acceptor.start() != 0) {
        std::cerr << "error: starting acceptor" << std::endl;
        return -1;
    }

    std::thread clientTh(client);

    Stream* stream = acceptor.accept();
    if (stream) {
        std::string msg = stream->recv(READ_BUFFER_SIZE);
        {
            std::lock_guard<std::mutex> guard(cout_mutex);
            std::cout << "server recieve:";
            for (int i = 0; i < msg.length(); ++i)
                std::cout << " " << (int)msg[i];
            std::cout << std::endl;
        }
        stream->send({ 1, 2, 3, 4, -1, -2, -3, -4 });

        delete stream;
    }


    clientTh.join();
    
    return 0;
}
