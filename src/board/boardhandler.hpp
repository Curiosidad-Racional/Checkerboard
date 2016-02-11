#ifndef __boardhandler_hpp__
#define __boardhandler_hpp__

#include "board.hpp"
#include "drawer.hpp"
#include "../tcp/stream.hpp"

class BoardHandler {
    Board* board;
    Drawer* drawer;
    Stream* stream;
public:
    BoardHandler(Board* );
    ~BoardHandler();

    void run();
    
    void update(const Location<unsigned char>& );
    Location<unsigned char>* key(const char& , const Location<unsigned char> );

    void setStream(Stream* _stream) { stream = _stream; }
};

#endif // __boardhandler_hpp__
