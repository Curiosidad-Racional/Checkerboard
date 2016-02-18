#include <iostream>
#include <string>

#include "board/board.hpp"
#include "board/boardhandler.hpp"
#include "tcp/stream.hpp"
#include "tcp/connector.hpp"


#define PORT 12321
#define MSG_SIZE 64



int main(int argc, char *argv[])
{

    // command arguments
    if ( argc < 1 || 3 < argc ) {
        std::cerr << "usage: " << argv[0] << " [<ip>] [<port>]" << std::endl;
        return -1;
    }

    // connector
    Connector connector = Connector();
    Stream* stream = NULL;

    switch (argc) {
    case 1:
        stream = connector.connect(PORT, "localhost");
        break;
    case 2:
        stream = connector.connect(PORT, argv[1]);
        break;
    case 3:
        stream = connector.connect(std::stoi(argv[2]), argv[1]);
        break;
    }

    // start comunication
    if (stream) {

        // first revieve
        std::string msg = stream->recv(MSG_SIZE);
        if (msg.length() < 1) {
            std::cerr << "error: first message failed" << std::endl;
            delete stream;
            return -1;            
        }

        // start board
        Board board(8);

        BoardHandler boardHandler(&board);
        boardHandler.setStream(stream);
        if (msg == "whte")
            boardHandler.setColor(Piece::white);
        else
            boardHandler.setColor(Piece::black);
        boardHandler.run();

    }
    
    return 0;
}
