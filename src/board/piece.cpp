#include "piece.hpp"
#include "board.hpp"

Piece::Piece(const piece_color_enum& _piece_color, Board* _board, const unsigned char& _x, const unsigned char& _y)
        : piece_color(_piece_color), board(_board), Location(_x, _y) {}


bool Piece::direction(const char& dy, const char& dx) {
    char i = y + dy*piece_color, j = x + dx;

    Piece* piece = board->move(this, i, j);
    if (piece != 0)
        if (piece == this) return true;
        else if (piece->piece_color != piece_color) {
            char ii = i + dy*piece_color, jj = j + dx;

            if (board->move(this, ii, jj) == this) {
                board->remove(i, j);
                return true;
            }
        }

    return false;
}


bool Piece::forwardLeft() {
    return direction(1, -1);
}

bool Piece::forwardRight() {
    return direction(1, 1);
}

Piece::piece_type_enum Piece::getType() const {
    switch (piece_color) {
    case white:
        return man_white; 
    case black:
        return man_black;
    }
}

Piece::piece_color_enum Piece::getColor() const {
    return piece_color;
}
