#include <cstdlib>
#include <string>
#include <iostream>

#include "drawer.hpp"
#include "boardhandler.hpp"

using namespace std;

char Drawer::pieceCharacter(const Piece::piece_type_enum& piece_type, const Piece::piece_color_enum& piece_color) {
     switch (piece_type) {
     case Piece::empty:
            return ' ';
     case Piece::man:
         switch (piece_color) {
         case Piece::white:
             return 'o';
         case Piece::black:
             return 'x';
         }
     case Piece::king:
         switch (piece_color) {
         case Piece::white:
             return 'O';
         case Piece::black:
             return 'X';
         }
     }
}

Drawer::Drawer(BoardHandler * _boardHandler, const unsigned char& _size)
    : y(1), x(2), location(NULL), boardHandler(_boardHandler), size(_size) {
    if ( (window = initscr()) == NULL ) {
	cerr << "error: main window startup.\n";
	exit(EXIT_FAILURE);
    }

    if ( (wininfo = newwin(12, 16, 1, 35)) == NULL ) {
	cerr << "error: info window startup.\n";
	exit(EXIT_FAILURE);
    }


    wininfo = newwin(12, 16, 1, 35);
    box(wininfo, 0, 0);

    raw();
    keypad(window, TRUE);
    noecho();
    curs_set(FALSE);

    start_color();

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLUE);
    init_pair(3, COLOR_WHITE, COLOR_RED);

    bkgd(COLOR_PAIR(1));
    wrefresh(window);

    drawBoard();
    drawInfo();
    drawCursor(2, y, x);
}


Drawer::~Drawer() {
    delwin(wininfo);
    delwin(window);
    endwin();
    refresh();
}


void Drawer::drawBoard() {
    unsigned char i, j;
    // First row
    waddch(window, ACS_ULCORNER);
    waddch(window, ACS_HLINE);
    
    for(i = 1; i < size; i++) {
        waddch(window, ACS_HLINE);
        waddch(window, ACS_HLINE);
        waddch(window, ACS_TTEE);
        waddch(window, ACS_HLINE);
    }
    
    waddch(window, ACS_HLINE);
    waddch(window, ACS_HLINE);
    waddch(window, ACS_URCORNER);

    // Rows
    for (j = 1; j < 2*size - 1; j += 2) {
        for (i = 0; i < size + 1; i++) {
            wmove(window, j, i*4); waddch(window, ACS_VLINE);
        }

        wmove(window, j + 1, 0);
        waddch(window, ACS_LTEE);
        waddch(window, ACS_HLINE);
    
        for(i = 1; i < size; i++) {
            waddch(window, ACS_HLINE);
            waddch(window, ACS_HLINE);
            waddch(window, ACS_PLUS);
            waddch(window, ACS_HLINE);
        }
    
        waddch(window, ACS_HLINE);
        waddch(window, ACS_HLINE);
        waddch(window, ACS_RTEE);
    }
    for (i = 0; i < size + 1; i++) {
        wmove(window, j, i*4); waddch(window, ACS_VLINE);
    }

    // Last row
    wmove(window, j+1, 0);
    waddch(window, ACS_LLCORNER);
    waddch(window, ACS_HLINE);
    
    for(i = 1; i < size; i++) {
        waddch(window, ACS_HLINE);
        waddch(window, ACS_HLINE);
        waddch(window, ACS_BTEE);
        waddch(window, ACS_HLINE);
    }
    
    waddch(window, ACS_HLINE);
    waddch(window, ACS_HLINE);
    waddch(window, ACS_LRCORNER);

    wrefresh(window);

}


void Drawer::drawInfo() {
    mvwprintw(wininfo, 1, 2, "Control keys");
    mvwprintw(wininfo, 3, 5, "arrows");
    mvwprintw(wininfo, 4, 5, "+ -");
    mvwprintw(wininfo, 5, 5, "space");
    mvwprintw(wininfo, 7, 2, "Other keys");
    mvwprintw(wininfo, 9, 5, "q - quit");
    wrefresh(wininfo);
}


void Drawer::drawPiece(const Piece::piece_type_enum& piece_type, const Piece::piece_color_enum& piece_color, const unsigned char& i, const unsigned char& j) {
    wmove(window, i, j);
    waddch(window, pieceCharacter(piece_type, piece_color));
    wrefresh(window);
}


void Drawer::drawCursor(const unsigned char& color,  const unsigned char& i, const unsigned char& j) {
    chtype current_char = mvwinch(window, i, j) & A_CHARTEXT;
    mvwaddch(window, i, j, current_char | COLOR_PAIR(color));
}    

void Drawer::drawMessage(const std::string msg) {
    mvwprintw(window, 14, 35, msg_clear.c_str());
    mvwprintw(window, 14, 35, msg.c_str());
    wrefresh(window);
    msg_clear.resize(msg.length(), ' ');
}

char Drawer::keyboard() {

    switch (wgetch(window)) {
    case KEY_LEFT:
        if (x < 4) break;
        // redraw cursor in new position
        drawCursor((const unsigned char)1, y, x);
        x -= 4;
        drawCursor((const unsigned char)2, y, x);
        // redraw pointer to the next move
        drawCursor((const unsigned char)1, location);
        location = boardHandler->key(BoardHandler::current, console2location(y, x));
        drawCursor((const unsigned char)3, location);
        // refresh
        wrefresh(window);
        break;
    case KEY_RIGHT:
        if (x > 4*size - 6) break;
        // redraw cursor in new position
        drawCursor((const unsigned char)1, y, x);
        x += 4;
        drawCursor((const unsigned char)2, y, x);
        // redraw pointer to the next move
        drawCursor((const unsigned char)1, location);
        location = boardHandler->key(BoardHandler::current, console2location(y, x));
        drawCursor((const unsigned char)3, location);
        // refresh
        wrefresh(window);
        break;
    case KEY_UP:
        if (y < 2) break;
        // redraw cursor in new position
        drawCursor((const unsigned char)1, y, x);
        y -= 2;
        drawCursor((const unsigned char)2, y, x);
        // redraw pointer to the next move
        drawCursor((const unsigned char)1, location);
        location = boardHandler->key(BoardHandler::current, console2location(y, x));
        drawCursor((const unsigned char)3, location);
        // refresh
        wrefresh(window);
        break;
    case KEY_DOWN:
        if (y > 2*size - 3) break;
        // redraw cursor in new position
        drawCursor((const unsigned char)1, y, x);
        y += 2;
        drawCursor((const unsigned char)2, y, x);
        // redraw pointer to the next move
        drawCursor((const unsigned char)1, location);
        location = boardHandler->key(BoardHandler::current, console2location(y, x));
        drawCursor((const unsigned char)3, location);
        // refresh
        wrefresh(window);
        break;
    case '+':
        // redraw pointer to the next move
        drawCursor((const unsigned char)1, location);
        location = boardHandler->key(BoardHandler::next, console2location(y, x));
        drawCursor((const unsigned char)3, location);
        // refresh
        wrefresh(window);            
        break;
    case '-':
        // redraw pointer to the next move
        drawCursor((const unsigned char)1, location);
        location = boardHandler->key(BoardHandler::previous, console2location(y, x));
        drawCursor((const unsigned char)3, location);
        // refresh
        wrefresh(window);            
        break;
    case ' ':
        // redraw cursor and pointer
        if (location == NULL) break;
        drawCursor((const unsigned char)1, y, x);
        drawCursor((const unsigned char)1, location);
        location = boardHandler->key(BoardHandler::move, console2location(y, x));
        x = location->getX()*4 + 2;
        y = location->getY()*2 + 1;
        drawCursor((const unsigned char)2, location);
        location = boardHandler->key(BoardHandler::current, *location);
        drawCursor(3, location);
        // refresh
        wrefresh(window);            
        break;
    case 'q':
        return 'q';
    }

    return '\0';

}
