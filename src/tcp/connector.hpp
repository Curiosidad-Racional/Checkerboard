#ifndef __connector_hpp__
#define __connector_hpp__

#include <netinet/in.h>

#include "stream.hpp"


class Connector
{
    int resolveHostName(const string , struct in_addr* );
    
public:
    
    Stream* connect(const unsigned int , const string = "localhost");
};

#endif // __connector_hpp__
