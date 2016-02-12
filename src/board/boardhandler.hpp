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

    enum keys { previous = -1, current = 0, next = 1, move = 100 };
    
    void run();
    
    void update(const Location<unsigned char>& );
    Location<unsigned char>* key(const keys , const Location<unsigned char> );

    void setStream(Stream* _stream) { stream = _stream; }
};

#endif // __boardhandler_hpp__
