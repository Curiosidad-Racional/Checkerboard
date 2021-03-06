#include <cstddef>

#include "man.hpp"
#include "king.hpp"
#include "board.hpp"


void Man::calcLocations() {
    unsigned char x, y;
    char dy;

    if (piece_color == white) {
        dy = - 1;
    } else {
        dy = 1;
    }

    for (unsigned char i = 0; i < 2; i++) {
        eat[i] = false;
        
        x = getX() - 1 + 2*i;
        y = getY() + dy;
        
        locations[i] = Location<unsigned char>(getSize(), x, y);
        if (locations[i].isValid()) {
            Piece* piece = board->piece(locations[i]);
            if (piece != NULL) {
                if (piece->getColor() == piece_color)
                    locations[i] = Location<unsigned char>(getSize(), -1, -1);
                else {
                    x += - 1 + 2*i;
                    y += dy;
                    Location<unsigned char> location(getSize(), x, y);
                    if (location.isValid()) {
                        piece = board->piece(location);
                        if (piece != NULL)
                            locations[i] = Location<unsigned char>(getSize(), -1, -1);
                        else {
                            eat[i] = true;
                            eat_locations[i] = locations[i];
                            locations[i] = location;
                        }
                    } else
                        locations[i] = location;
                }
            }                
        }
    }
}


bool Man::preMove() {
    
    if (eat[location_index]) board->remove(eat_locations[location_index]);

    return true;
}


Location<unsigned char>* Man::postMove() {

    if (piece_color == white && getY() == 0) {
        King* king = new King(piece_color, board, (Location<unsigned char>)*this);
        board->put(king);
        return king;
    } else if (piece_color == black && getY() == getSize() - 1) {
        King* king = new King(piece_color, board, (Location<unsigned char>)*this);
        board->put(king);
        return king;        
    } else
        return this;
}
