#ifndef __piece_hpp__
#define __piece_hpp__


#include <exception>

class Board;

#include "location.hpp"


struct infinite_loop : public std::exception
{
  const char * what () const throw ()
  {
    return "Infinite loop exception";
  }
};


class Piece : public Location<unsigned char> {
    friend class Board;
    Board* board;

    Location<unsigned char> getLocation() const;
    void update(const Location<unsigned char> );

public:
    enum piece_color_enum { white = -1, black = 1 };
    enum piece_type_enum { empty = -1, man_white = 1, king_white, man_black, king_black };

    Piece(const piece_color_enum& _piece_color, Board* _board, const Location<unsigned char>& _location, const unsigned char& _n);
    virtual ~Piece();
    
    piece_color_enum getColor() const;
    virtual piece_type_enum getType() const = 0;

    Location<unsigned char>* currLocation();
    Location<unsigned char>* nextLocation() throw(infinite_loop);
    Location<unsigned char>* prevLocation() throw(infinite_loop);
    virtual Location<unsigned char>* move();
protected:
    virtual void calcLocations() = 0;
    unsigned long int location_index, location_size;
    Location<unsigned char>* locations;

    piece_color_enum piece_color;

    Piece(Piece& );
};


#endif // __piece_hpp__