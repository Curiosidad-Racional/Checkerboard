#include <iostream>
#include <thread>
#include <string>
#include <mutex>

#include "../src/tcp/stream.hpp"
#include "../src/tcp/connector.hpp"
#include "../src/tcp/acceptor.hpp"


std::mutex cout_mutex;

void client() {
    Connector connector;

    Stream* stream = connector.connect(1234);

    if (stream) {
        stream->send("Hola");
        std::string msg = stream->recv(64);
        {
            std::lock_guard<std::mutex> guard(cout_mutex);
            std::cout << "client recieve: " << msg << std::endl;
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
        std::string msg = stream->recv(64);
        {
            std::lock_guard<std::mutex> guard(cout_mutex);
            std::cout << "server recieve: " << msg << std::endl;
        }
        stream->send("Adios");

        delete stream;
    }


    clientTh.join();
    
    return 0;
}
