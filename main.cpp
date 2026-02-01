#include <iostream>
#include <string>
#include <vector>

#include "Pieces.h"
#include "ChessBoard.h"

int main()
{
    ChessBoard<Piece*> board;
    std::vector<std::string> layout(8);

    std::cout << "Welcome to Chess Analyzer!\n";
    std::cout << "Input each row:\n";
    std::cout << "  ABCDEFGH\n";

    for (int i = 0; i < 8; ++i)
    {
        std::cout << i + 1 << " ";
        std::cin >> layout[i];
    }

    board.loadBoard(layout);

    char color;
    std::cout << "Enter color to be checkmated (W/B): ";
    std::cin >> color;

    char opponent = (color == 'W') ? 'B' : 'W';

    if (board.isCheckmate(color))
    {
        std::cout << "Checkmate detected!\n";
        return 0;
    }

    std::cout << "There is no checkmate now.\n";

    if (board.isMateInOne(opponent))
    {
        std::cout << "Checkmate is possible in one move.\n";
    }
    else
    {
        std::cout << "No mate in one exists.\n";
    }

    return 0;
}