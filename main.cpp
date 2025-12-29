#include <iostream>
#include <string>
#include <vector>
#include "Pieces.h"
#include "ChessBoard.h"


int main() {
    ChessBoard<Piece*> board;
    std::vector<std::string> layout(8);
    char c;
    std::cout << "Welcome to Chess Analyzer!" << std::endl;
    std::cout << "Input each row:" << std::endl;
    std::cout << " ABCDEFGH" << std::endl;
    for(int i = 0; i < 8; i++)
    {
        std::cout << i+1;
        std::cin >> layout[i];
    }

    board.loadBoard(layout);

    std::cout << "Enter which color do you want to check to be checkmated: ";
    std::cin >> c;

    if(board.isCheckmate(c))
    {
        std::cout << "Checkmate detected!" << std::endl;
    }
    else
    {
        std::cout << "There is no checkmate!" << std::endl;
    }
    return 0;
}