#include <cstddef>

#include "king.hpp"
#include "board.hpp"


void King::calcLocations() {
    unsigned char x, y;

    for (unsigned char i = 0; i < 4; i++) {
        eat[i] = false;
        
        x = getX() - 1 + 2*(i%2);
        y = getY() - 1 + 2*(i/2);
        
        locations[i] = Location<unsigned char>(getSize(), x, y);
        if (locations[i].isValid()) {
            Piece* piece = board->piece(locations[i]);
            if (piece != NULL) {
                if (piece->getColor() == piece_color)
                    locations[i] = Location<unsigned char>(getSize(), -1, -1);
                else {
                    x += - 1 + 2*(i%2);
                    y += - 1 + 2*(i/2);
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


bool King::preMove() {
    
    if (eat[location_index]) board->remove(eat_locations[location_index]);

    return true;
}
