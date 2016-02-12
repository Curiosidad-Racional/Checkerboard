#ifndef __man_hpp__
#define __man_hpp__


#include "piece.hpp"


class Man : public Piece {
    bool eat[2];
    Location<unsigned char> eat_locations[2];

public:

    Man(const piece_color_enum& _piece_color, Board* _board, const Location<unsigned char>& _location)
        : Piece(_piece_color, _board, _location, 2) {
        calcLocations();
    }
    ~Man() {}

    piece_type_enum getType() const { return man; }

    void calcLocations();
    bool preMove();
    Location<unsigned char>* postMove();

};


#endif // __man_hpp__
