#ifndef __piece_hpp__
#define __piece_hpp__


class Board;

#include "location.hpp"


class Piece : public Location<unsigned char> {
    friend class Board;
    
    Location<unsigned char> getLocation() const;
    void update(const Location<unsigned char> );

public:
    
    enum piece_color_enum { white = -1, undefined = 0, black = 1 };
    enum piece_type_enum { empty = 10, man, king };

    Piece(const piece_color_enum& _piece_color, Board* _board, const Location<unsigned char>& _location, const unsigned char& _n);
    virtual ~Piece();
    
    piece_color_enum getColor() const;
    virtual piece_type_enum getType() const = 0;

    Location<unsigned char>* currLocation();
    Location<unsigned char>* nextLocation();
    Location<unsigned char>* prevLocation();
    Location<unsigned char>* move();

protected:

    Board* board;
    virtual void calcLocations() = 0;
    virtual bool preMove() { return true; }
    virtual Location<unsigned char>* postMove() { return this; }
    unsigned long int location_index, location_size;
    Location<unsigned char>* locations;

    piece_color_enum piece_color;

    Piece(Piece& );
};


#endif // __piece_hpp__
