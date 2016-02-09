#ifndef __board_hpp__
#define __board_hpp__

class BoardHandler;

#include "piece.hpp"

class Board {
    friend class Piece;
    const unsigned char size;
    Piece*** pieces;
    Piece* move(Piece* , const unsigned char&, const unsigned char& );
    bool remove(const unsigned char& , const unsigned char& );
    BoardHandler* boardHandler;
    Board(const Board& );
public:
    Board(const unsigned char& );
    ~Board();

    unsigned char getSize() const { return size; }

    void setHandler(BoardHandler* _boardHandler) { boardHandler = _boardHandler; }

    Piece* piece(const unsigned char& , const unsigned char& );
};

#endif // __board_hpp__
