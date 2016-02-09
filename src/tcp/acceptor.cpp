#include <arpa/inet.h>
#include <string.h>
#include <iostream>

#include "acceptor.hpp"


#define LISTEN_BACKLOG 50

Acceptor::~Acceptor()
{
    if (sd > 0) {
        close(sd);
    }
}

int Acceptor::start()
{
    if (started == true) {
        return 0;
    }

    sd = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in _address;

    memset(&_address, 0, sizeof(_address));
    _address.sin_family = PF_INET;
    _address.sin_port = htons(port);
    
    if (address.size() > 0) {
        inet_pton(PF_INET, address.c_str(), &(_address.sin_addr));
    } else {
        _address.sin_addr.s_addr = INADDR_ANY;
    }
    
    int optval = 1;
    int result = setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    if (result != 0) {
        std::cerr << "error: setsockopt() failed" << std::endl;
        return result;
    }
    
    result = bind(sd, (struct sockaddr*)&_address, sizeof(_address));
    if (result != 0) {
        std::cerr << "error: bind() failed" << std::endl;
        return result;
    }
    
    result = listen(sd, LISTEN_BACKLOG);
    if (result != 0) {
        std::cerr << "error: listen() failed" << std::endl;
        return result;
    }
    
    started = true;
    
    return result;
}

Stream* Acceptor::accept() 
{
    if (started == false) {
        return NULL;
    }

    struct sockaddr_in _address;
    socklen_t len = sizeof(_address);
    memset(&_address, 0, sizeof(_address));
    int asd = ::accept(sd, (struct sockaddr*)&_address, &len);
    if (asd < 0) {
        perror("accept() failed");
        return NULL;
    }
    return new Stream(asd, &_address);
}
