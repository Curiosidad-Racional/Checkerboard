#ifndef __drawer_hpp__
#define __drawer_hpp__

#include <ncurses.h>

class BoardHandler;

#include "piece.hpp"

class Drawer {
    // pointer to the next move
    Location<unsigned char>* location;
    // cursor position
    unsigned char y, x;

    std::string msg_clear;

    BoardHandler* boardHandler;
    unsigned char size;
    
    WINDOW* window;
    WINDOW* wininfo;

    void drawBoard();
    void drawInfo();

    char pieceCharacter(const Piece::piece_type_enum& , const Piece::piece_color_enum& );
    Location<unsigned char> console2location(unsigned char& y, unsigned char& x) {
        return Location<unsigned char>(size, (x - 2)/4, (y - 1)/2);
    }
public:
    Drawer(BoardHandler* , const unsigned char& );
    ~Drawer();

    void drawPiece(const Piece::piece_type_enum& type, const Piece::piece_color_enum& color, const Location<unsigned char> location) {
        drawPiece(type, color, location.getY()*2 + 1, location.getX()*4 + 2);
    }
    void drawCursor(const unsigned char& color, const Location<unsigned char>* location) {
        if (location == NULL) return;
        drawCursor(color, location->getY()*2 + 1, location->getX()*4 + 2);
    }

    void drawPiece(const Piece::piece_type_enum& , const Piece::piece_color_enum& , const unsigned char& , const unsigned char& );
    void drawCursor(const unsigned char& , const unsigned char& , const unsigned char&  );
    void drawMessage(const std::string );

    char keyboard();
};

#endif // __drawer_hpp__
