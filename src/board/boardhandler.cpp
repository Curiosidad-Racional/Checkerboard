#include <cstdlib>
#include <string>
#include <iostream>


#include "boardhandler.hpp"
#include "piece.hpp"
#include "man.hpp"
#include "king.hpp"


void BoardHandler::waitOpponent() throw(wrong_piece_type) {
    if (stream == NULL) return;

    std::string msg = stream->recv(64);

    if (msg.length() == 0) {
        std::cerr << "error: connection broken" << std::endl;
        exit(0);
    }
    
    for (unsigned char i = 0; i < msg.length(); i += 4) {
        const Piece::piece_color_enum piece_color = (Piece::piece_color_enum)msg[i+1];
        const Location<unsigned char> location(board->getSize(), msg[i+2], msg[i+3]);

        switch (msg[i]) {
        case Piece::empty: {
            board->remove(location);
            drawer->drawPiece(Piece::empty, Piece::black, location);
            // breaks function
            return;
            break;
        }
        case Piece::man: {
            Piece* piece = new Man(piece_color, board, location);
            board->put(piece);
            drawer->drawPiece(piece->getType(), piece->getColor(), location);
            break;
        }
        case Piece::king: {
            Piece* piece = new King(piece_color, board, location);
            board->put(piece);
            drawer->drawPiece(piece->getType(), piece->getColor(), location);
            break;
        }
        default:
            throw wrong_piece_type();
        }
    }
}


BoardHandler::BoardHandler(Board* _board)  : board(_board) {
    stream = NULL;
    
    drawer = new Drawer(this, board->getSize());
    for (unsigned char i = 0; i < board->getSize(); i++)
        for (unsigned char j = 0; j < board->getSize(); j++) {
            Location<unsigned char> location(board->getSize(), j, i);
            Piece* piece = board->piece(location);
            if (piece != NULL)
                drawer->drawPiece(piece->getType(), piece->getColor(), location);
        }
    
    board->setHandler(this);

    handler_color = Piece::undefined;
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
        drawer->drawPiece(piece->getType(), piece->getColor(), location);
        if (stream != NULL)
            stream->send({piece->getType(), piece->getColor(), (char)location.getX(), (char)location.getY()});
    } else {
        drawer->drawPiece(Piece::empty, Piece::black, location);
        if (stream != NULL)
            stream->send({Piece::empty, Piece::black, (char)location.getX(), (char)location.getY()});
    }
}

Location<unsigned char>* BoardHandler::key(const keys key_code, const Location<unsigned char> location) {
    Piece* piece = board->piece(location);
    if (piece == NULL) return NULL;

    if (handler_color != Piece::undefined)
        if (handler_color != piece->getColor()) return NULL;

    Location<unsigned char>* result = NULL;
    switch (key_code) {
    case next:
        result = piece->nextLocation();
        break;
    case current:
        result = piece->currLocation();
        break;
    case previous:
        result = piece->prevLocation();
        break;
    case move:
        result = piece->move();
        break;
    }

    if (result != NULL) waitOpponent();

    return result;
}
