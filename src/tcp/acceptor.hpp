#ifndef __acceptor_hpp__
#define __acceptor_hpp__

#include <string>
#include <netinet/in.h>

#include "stream.hpp"

using namespace std;

class Acceptor
{
    bool started;
    unsigned int sd; // socket descriptor
    unsigned int port;
    string address;

    Acceptor() {}
    
public:

    Acceptor(const unsigned int _port, const string _address = "")
        : sd(0), port(_port), address(_address), started(false) {} 
    ~Acceptor();

    int start();
    Stream* accept();

};

#endif // __acceptor_hpp__
