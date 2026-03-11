#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include "Pieces.h"
#include "ChessBoard.h" 
    
int main()
{
    ChessBoard<Piece*> board;
    std::vector<std::string> layout(8);

    std::cout << "Welcome to Chess Analyzer!\n";
    std::cout << "1. Input board manually\n2. Read board from file\nChoice: ";
    int choice;
    std::cin >> choice;

    if (choice == 2)
    {
        std::string filename;
        std::cout << "Enter filename:  ";
        std::cin >> filename;
        std::ifstream file(filename);
        if (!file)
        {
            std::cout << "Error: File not found.\n";
            return 1;
        }
        for (int i = 0; i < 8; ++i)
        {
            file >> layout[i];
        }
    }
    else
    {
        std::cout << "Input each row:\n";

        std::cout << "  ABCDEFGH\n";
        for (int i = 0; i < 8; ++i)
        {
            std::cout << i + 1 << " ";
            std::cin >> layout[i];
        }
    }

    board.loadBoard(layout);

    char color;
    std::cout << "Enter color to be checkmated (W/B): ";
    std::cin >> color;

    char opponent = (color == 'W') ? 'B' : 'W';

    if(board.isCheckmate(color))
    {
        std::cout << "Success: Mate detected!" << std::endl;
    }   
    else if (board.isMateInOne(opponent)) 
    {
        std::cout << "Success: Mate in One detected!" << std::endl;
    } 
    else if (board.isMateInTwo(opponent)) 
    {
        std::cout << "Success: Mate in Two detected!" << std::endl;
    } 
    else 
    {
        std::cout << "There is no mate for the selected color in this range." << std::endl;
    }

    return 0; 
}