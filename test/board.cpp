#include <iostream>

#include "../src/board/board.hpp"
#include "../src/board/boardhandler.hpp"

int main(int argc, char *argv[])
{
    Board board(8);

    BoardHandler boardHandler(&board);
    boardHandler.run();
    
    return 0;
}
