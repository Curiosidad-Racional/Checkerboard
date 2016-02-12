#ifndef __drawer_hpp__
#define __drawer_hpp__

#include <ncurses.h>

class BoardHandler;

#include "piece.hpp"

class Drawer {
    BoardHandler* boardHandler;
    unsigned char size;
    
    WINDOW* window;
    WINDOW* wininfo;

    void drawBoard();
    void drawInfo();

    char pieceCharacter(const Piece::piece_type_enum& );
    Location<unsigned char> console2location(unsigned char& y, unsigned char& x) {
        return Location<unsigned char>(size, (x - 2)/4, (y - 1)/2);
    }
public:
    Drawer(BoardHandler* , const unsigned char& );
    ~Drawer();

    void drawPiece(const Piece::piece_type_enum& type, const Location<unsigned char> location) {
        drawPiece(type, location.getY()*2 + 1, location.getX()*4 + 2);
    }
    void drawCursor(const unsigned char& color, const Location<unsigned char>* location) {
        if (location == NULL) return;
        drawCursor(color, location->getY()*2 + 1, location->getX()*4 + 2);
    }

    void drawPiece(const Piece::piece_type_enum& , const unsigned char& , const unsigned char& );
    void drawCursor(const unsigned char& , const unsigned char& , const unsigned char&  );

    void run();
};

#endif // __drawer_hpp__
