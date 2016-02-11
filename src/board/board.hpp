#ifndef __board_hpp__
#define __board_hpp__

#include <exception>

class BoardHandler;

#include "piece.hpp"


struct overboard_location : public std::exception
{
  const char * what () const throw ()
  {
    return "Overboard location exception";
  }
};

struct inconsistent_piece : public std::exception
{
  const char * what () const throw ()
  {
    return "Inconsistent piece exception";
  }
};


class Board {
    const unsigned char size;
    Piece*** pieces;
    BoardHandler* boardHandler;
    Board(const Board& );

    bool checkPieceLocation(Piece* );
public:
    Board(const unsigned char& );
    ~Board();

    unsigned char getSize() const { return size; }

    void setHandler(BoardHandler* _boardHandler) { boardHandler = _boardHandler; }

    Piece*& piece(const Location<unsigned char>& ) throw(overboard_location);

    void swap(Piece* , Piece* );
    void move(Piece* , const Location<unsigned char>& );
    void remove(Piece* ) throw(inconsistent_piece);
};

#endif // __board_hpp__