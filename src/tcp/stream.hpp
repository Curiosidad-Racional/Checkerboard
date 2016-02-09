#ifndef __stream_hpp__
#define __stream_hpp__

#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

using namespace std;

class Stream
{
    unsigned int asd; // accepted socket descriptor
    string ip;
    unsigned int port;
    
    Stream(const unsigned int , const struct sockaddr_in* );
    Stream();
    Stream(const Stream& );

  public:

    ~Stream();

    friend class Acceptor;
    friend class Connector;

    ssize_t send(const string buffer);
    string recv(const size_t len);

    string getIp() const;
    unsigned int getPort() const;
};

#endif // __stream_hpp__
