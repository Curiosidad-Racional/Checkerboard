#ifndef __piece_hpp__
#define __piece_hpp__

class Board;

#include "location.hpp"


class Piece : public Location<unsigned char> {
    friend class Board;
    Board* board;
public:
    enum piece_color_enum { white = -1, black = 1 };
    enum piece_type_enum { empty, man_white, king_white, man_black, king_black };

    Piece(const piece_color_enum& _piece_color, Board* _board, const unsigned char& _x, const unsigned char& _y);
    virtual ~Piece() {}
    
    bool forwardLeft();
    bool forwardRight();
    piece_color_enum getColor() const;
    virtual bool backwardLeft() { return false; }
    virtual bool backwardRight() { return false;}
    virtual piece_type_enum getType() const;
protected:
    piece_color_enum piece_color;

    Piece(Piece& );
    bool direction(const char& , const char& );
};


#endif // __piece_hpp__
