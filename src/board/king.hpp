#ifndef __king_hpp__
#define __king_hpp__

#include "piece.hpp"

class King : public Piece {
public:
    King(const piece_color_enum& _piece_color, Board* _board, const unsigned char& _x, const unsigned char& _y)
        : Piece(_piece_color, _board, _x, _y) {}
    bool backwardLeft() { return direction(-1, -1); }
    bool backwardRight() { return direction(-1, 1); }
    piece_type_enum getType() const {
        switch (piece_color) {
        case white:
            return king_white; 
        case black:
            return king_black;
        }
    }
};

#endif // __king_hpp__
