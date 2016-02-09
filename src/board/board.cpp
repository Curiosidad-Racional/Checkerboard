#include <typeinfo>

#include "board.hpp"
#include "boardhandler.hpp"
#include "king.hpp"

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
            pieces[i][j] = new Piece(Piece::black, this, j, i);

    // Whites
    // Create pieces
    for (i = size - 3; i < size; i++)
        for (j = (i+1)%2; j < size; j += 2)
            pieces[i][j] = new Piece(Piece::white, this, j, i);
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


Piece* Board::move(Piece* piece, const unsigned char& i, const unsigned char& j) {
    // Check dimentions
    if (size <= i || size <= j) return 0;
    
    // Check empty location
    if (pieces[i][j] != NULL) return pieces[i][j];

    pieces[i][j] = piece;
    pieces[piece->y][piece->x] = NULL;
    if (boardHandler != NULL) boardHandler->update(piece->y, piece->x);
    piece->x = j; piece->y = i;
    if (boardHandler != NULL) boardHandler->update(i, j);

    return piece;
}


bool Board::remove(const unsigned char& i, const unsigned char& j) {
    // Check dimentions
    if (size <= i || size <= j) return false;

    // Check empty location
    if (pieces[i][j] != NULL) {
        delete pieces[i][j];
        pieces[i][j] = NULL;
        if (boardHandler != NULL) boardHandler->update(i, j);
    }

    return true;
}



Piece* Board::piece(const unsigned char& i, const unsigned char& j) {
    // Check dimentions
    if (size <= i || size <= j) return 0;
    
    return pieces[i][j];
}
