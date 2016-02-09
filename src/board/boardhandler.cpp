#include <iostream>
#include "boardhandler.hpp"
#include "piece.hpp"

BoardHandler::BoardHandler(Board* _board)  : board(_board) {
    drawer = new Drawer(this, board->getSize());
    for (unsigned char i = 0; i < board->getSize(); i++)
        for (unsigned char j = 0; j < board->getSize(); j++) {
            Piece* piece = board->piece(i, j);
            if (piece != NULL) drawer->drawPiece(piece->getType(), i, j);
        }
    
    board->setHandler(this);
}


BoardHandler::~BoardHandler()  {
    delete drawer;
}


void BoardHandler::run() {
    drawer->run();
}


void BoardHandler::update(const unsigned char& i, const unsigned char& j) {
    Piece* piece = board->piece(i, j);
    if (piece != NULL) drawer->drawPiece(piece->getType(), i, j);
    else drawer->drawPiece(Piece::empty, i, j);
}

bool BoardHandler::key(const unsigned char& key_code, const unsigned char& i, const unsigned char& j) {
    if (board->getSize() <= i || board->getSize() <= j) return false;

    Piece* piece = board->piece(i, j);
    if (piece == NULL) return false;

    switch (key_code) {
    case 1:
        if (piece->getColor() == Piece::black)
            return piece->forwardLeft();
        else
            return piece->backwardLeft();
        break;
    case 3:
        if (piece->getColor() == Piece::black)
            return piece->forwardRight();
        else
            return piece->backwardRight();
        break;
    case 7:
        if (piece->getColor() != Piece::black)
            return piece->forwardLeft();
        else
            return piece->backwardLeft();
        break;
    case 9:
        if (piece->getColor() != Piece::black)
            return piece->forwardRight();
        else
            return piece->backwardRight();
        break;
    }

    return false;
}
