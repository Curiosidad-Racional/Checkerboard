#ifndef __king_hpp__
#define __king_hpp__

#include "piece.hpp"

class King : public Piece {
public:
    King(const piece_color_enum& _piece_color, Board* _board, const Location<unsigned char>& _location)
        : Piece(_piece_color, _board, _location, 4) {
        calcLocations();
    }

    
    piece_type_enum getType() const {
        switch (piece_color) {
        case white:
            return king_white; 
        case black:
            return king_black;
        }
    }

    void calcLocations() {
        locations[0] = Location(getSize(), getX() + 1, getY() + 1);
        locations[1] = Location(getSize(), getX() + 1, getY() - 1);
        locations[2] = Location(getSize(), getX() - 1, getY() + 1);
        locations[3] = Location(getSize(), getX() - 1, getY() - 1);
    }

};

#endif // __king_hpp__
