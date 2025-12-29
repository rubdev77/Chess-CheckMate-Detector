#include <iostream>
#include <string>
#include <vector>
#include "Pieces.h"
#include "ChessBoard.h"


int main() {
    ChessBoard<Piece*> board;
    std::vector<std::string> layout = {
    "....k...",
    "........",
    "........",
    "........",
    ".......b",
    "........",
    "...PP...",
    "...QKB.."
    };
    
    board.loadBoard(layout);
    
    if(board.isCheckmate('W')) {
        std::cout << "Checkmate Detected!" << std::endl;
    } else {
        std::cout << "Not Checkmate." << std::endl;
    }
    return 0;
}