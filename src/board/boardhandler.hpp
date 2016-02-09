#ifndef __boardhandler_hpp__
#define __boardhandler_hpp__

#include "board.hpp"
#include "drawer.hpp"

class BoardHandler {
    Board* board;
    Drawer* drawer;
public:
    BoardHandler(Board* );
    ~BoardHandler();

    void run();
    
    void update(const unsigned char& , const unsigned char& );
    bool key(const unsigned char& , const unsigned char& , const unsigned char& );
};

#endif // __boardhandler_hpp__
