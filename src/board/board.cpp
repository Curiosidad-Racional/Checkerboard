#include <typeinfo>

#include "board.hpp"
#include "boardhandler.hpp"
#include "man.hpp"
#include "king.hpp"


bool Board::checkPieceLocation(Piece* _piece) {
    if (piece(_piece->getLocation()) == _piece)
        return true;
    else
        return false;
}


Board::Board(const unsigned char& _size) : size(_size) {
    unsigned char i, j;

    boardHandler = NULL;

    // Create squares
    pieces = new Piece** [size];
    for (i = 0; i < size; i++)
        pieces[i] = new Piece* [size] { NULL };

    // Draughts board
    // Blacks
    // Create pieces
    for (i = 0; i < 3; i++)
        for (j = (i+1)%2; j < size; j += 2)
            pieces[i][j] = new Man(Piece::black, this, Location<unsigned char>(size, j, i));

    // Whites
    // Create pieces
    for (i = size - 3; i < size; i++)
        for (j = (i+1)%2; j < size; j += 2)
            pieces[i][j] = new Man(Piece::white, this, Location<unsigned char>(size, j, i));
}


Board::~Board() {
    unsigned char i, j;

    // Delete pieces
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            if (pieces[i][j] != NULL) delete pieces[i][j];

    // Delete squares
    for (i = 0; i < size; i++)
        delete[] pieces[i];
    delete[] pieces;
}


void Board::swap(Piece* piece_a, Piece* piece_b) {

    Location<unsigned char> location_a = piece_a->getLocation();
    Location<unsigned char> location_b = piece_b->getLocation();
    piece(location_a) = piece_b;
    piece(location_b) = piece_a;
    
    if (boardHandler != NULL) {
        boardHandler->update(location_a);
        boardHandler->update(location_b);
    }

    piece_a->update(location_b);
    piece_b->update(location_a);
}


void Board::move(Piece* piece_from, const Location<unsigned char>& location_to) {

    Piece* piece_to = piece(location_to);
    if (piece_to != NULL) remove(piece_to);

    Location<unsigned char> location_from = piece_from->getLocation();
    piece(location_to) = piece_from;
    piece(location_from) = NULL;

    if (boardHandler != NULL) {
        boardHandler->update(location_to);
        boardHandler->update(location_from);        
    }

    piece_from->update(location_to);
}


void Board::remove(Piece* _piece) throw(inconsistent_piece) {
    if (_piece == NULL) return;
    // Check piece location
    if (!checkPieceLocation(_piece)) throw inconsistent_piece();

    Location<unsigned char> location = _piece->getLocation();
    piece(location) = NULL;

    if (boardHandler != NULL)
        boardHandler->update(location);
    
    delete _piece;
}



Piece*& Board::piece(const Location<unsigned char>& location) throw(overboard_location) {
    // Check dimentions
    if (!(location.isValid())) throw overboard_location();
    
    return pieces[location.getY()][location.getX()];
}
