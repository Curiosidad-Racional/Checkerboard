#ifndef __boardhandler_hpp__
#define __boardhandler_hpp__

#include <exception>

#include "board.hpp"
#include "drawer.hpp"
#include "../tcp/stream.hpp"

struct wrong_piece_type : public std::exception
{
  const char * what () const throw ()
  {
    return "Wrong piece type exception";
  }
};


class BoardHandler {
    Piece::piece_color_enum handler_color;
    Board* board;
    Drawer* drawer;
    Stream* stream;

    void waitOpponent() throw(wrong_piece_type);
    
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
