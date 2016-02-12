#ifndef __king_hpp__
#define __king_hpp__

#include "piece.hpp"

class King : public Piece {
    bool eat[4];
    Location<unsigned char> eat_locations[4];

public:
    
    King(const piece_color_enum& _piece_color, Board* _board, const Location<unsigned char>& _location)
        : Piece(_piece_color, _board, _location, 4) {
        calcLocations();
    }

    
    piece_type_enum getType() const;

    void calcLocations();
    bool preMove();

};

#endif // __king_hpp__
