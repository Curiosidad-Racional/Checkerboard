#include <netdb.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>
#include <iostream>

#include "connector.hpp"


Stream* Connector::connect(const unsigned int port, const string address)
{
    struct sockaddr_in _address;

    memset (&_address, 0, sizeof(_address));
    _address.sin_family = AF_INET;
    _address.sin_port = htons(port);
    
    if (resolveHostName(address, &(_address.sin_addr)) != 0 ) {
        inet_pton(PF_INET, address.c_str(), &(_address.sin_addr));        
    }
    
    int sd = socket(AF_INET, SOCK_STREAM, 0);
    if (::connect(sd, (struct sockaddr*)&_address, sizeof(_address)) != 0) {
        std::cerr << "error: connect() failed" << std::endl;
        return NULL;
    }
    
    return new Stream(sd, &_address);
}


int Connector::resolveHostName(const string hostname, struct in_addr* address) 
{
    struct addrinfo *ainfo;
  
    int result = getaddrinfo(hostname.c_str(), NULL, NULL, &ainfo);
    if (result == 0) {
        memcpy(address, &((struct sockaddr_in*)ainfo->ai_addr)->sin_addr, sizeof(struct in_addr));
        freeaddrinfo(ainfo);
    }
    return result;
}
