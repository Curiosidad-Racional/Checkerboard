#include <arpa/inet.h>

#include "stream.hpp"

Stream::Stream(const unsigned int _asd, const struct sockaddr_in* address) : asd(_asd) {
    ip.resize(64, '\0');
    inet_ntop(PF_INET, (struct in_addr*)&(address->sin_addr.s_addr), &ip[0], ip.length()-1);
    port = ntohs(address->sin_port);
}

Stream::~Stream()
{
    close(asd);
}

ssize_t Stream::send(const string buffer) 
{
    return write(asd, buffer.c_str(), buffer.length());
}

std::string Stream::recv(size_t len) 
{
    std::string buffer(len + 1, '\0');
    ssize_t readed;
    
    readed = read(asd, &buffer[0], len);
    buffer[readed] = '\0';
    
    return buffer;
}

string Stream::getIp() const
{
    return ip;
}

unsigned int Stream::getPort() const
{
    return port;
}
