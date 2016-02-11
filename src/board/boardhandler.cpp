#include <iostream>
#include "boardhandler.hpp"
#include "piece.hpp"

BoardHandler::BoardHandler(Board* _board)  : board(_board) {

    stream = NULL;
    
    drawer = new Drawer(this, board->getSize());
    for (unsigned char i = 0; i < board->getSize(); i++)
        for (unsigned char j = 0; j < board->getSize(); j++) {
            Location<unsigned char> location(board->getSize(), j, i);
            Piece* piece = board->piece(location);
            if (piece != NULL) drawer->drawPiece(piece->getType(), location);
        }
    
    board->setHandler(this);
}


BoardHandler::~BoardHandler()  {
    delete drawer;
}


void BoardHandler::run() {
    drawer->run();
}


void BoardHandler::update(const Location<unsigned char>& location) {
    Piece* piece = board->piece(location);
    if (piece != NULL) {
        drawer->drawPiece(piece->getType(), location);
        //if (stream != NULL) 
    } else {
        drawer->drawPiece(Piece::empty, location);
        //if (stream != NULL)
    }
}

Location<unsigned char>* BoardHandler::key(const char& key_code, const Location<unsigned char> location) {
    Piece* piece = board->piece(location);
    if (piece == NULL) return NULL;

    Location<unsigned char>* result = NULL;
    switch (key_code) {
    case 1:
        result = piece->nextLocation();
        break;
    case 0:
        result = piece->currLocation();
        break;
    case -1:
        result = piece->prevLocation();
        break;
    case 100:
        result = piece->move();
        break;
    }

    //if (result != NULL && stream != NULL) moved();

    return result;
}
