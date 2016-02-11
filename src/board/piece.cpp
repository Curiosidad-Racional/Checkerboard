#include <iostream>

#include "piece.hpp"
#include "board.hpp"


Piece::Piece(const piece_color_enum& _piece_color, Board* _board, const Location<unsigned char>& _location, const unsigned char& _n)
    : piece_color(_piece_color), board(_board),
      location_index(0), location_size(_n), Location(_location) {
    locations = new Location<unsigned char>[_n];
    
    for (unsigned char i = 0; i < _n; ++i)
        locations[i].setSize(getSize());
}

Piece::~Piece() {
    delete[] locations;
}

Piece::piece_color_enum Piece::getColor() const {
    return piece_color;
}


Location<unsigned char> Piece::getLocation() const {
    return Location<unsigned char>(getSize(), x, y);
}


void Piece::update(const Location<unsigned char> location) {
    setX(location.getX());
    setY(location.getY());

    calcLocations();
}


Location<unsigned char>* Piece::currLocation() {
    calcLocations();
    
    return &locations[location_index];
}


Location<unsigned char>* Piece::nextLocation() throw(infinite_loop) {
    unsigned long int initial_value = location_index;

    do {
        location_index = (++location_index)%location_size;
        if (location_index == initial_value) throw infinite_loop();
    } while (!locations[location_index].isValid());
    
    return &locations[location_index];
}


Location<unsigned char>* Piece::prevLocation() throw(infinite_loop) {
    unsigned long int initial_value = location_index;

    do {
        location_index = (--location_index)%location_size;
        if (location_index == initial_value) throw infinite_loop();
    } while (!locations[location_index].isValid());
    
    return &locations[location_index];
}


Location<unsigned char>* Piece::move() {
    board->move(this, locations[location_index]);
    return this;
}
