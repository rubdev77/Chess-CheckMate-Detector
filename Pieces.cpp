#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include "Pieces.h"
#include "ChessBoard.h"

King::King(char c, int x, int y) : Piece(c, x, y) {}

bool King::canMove(int toX, int toY, const ChessBoard<Piece*>& board) 
{
    // implementing base cases
    if (toX == x && toY == y) 
    return false;
    if (toX < 0 || toX > 7 || toY < 0 || toY > 7) 
    return false;
    if(board[toY][toX]!=nullptr && (board[toY][toX]->getColor()==this->getColor()))
    return false;

    // implementing every case
    if(std::max(abs(toX-x), abs(toY - y))==1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Knight::Knight(char c, int x, int y) : Piece(c, x, y) {}

bool Knight::canMove(int toX, int toY, const ChessBoard<Piece*>& board)  
{
    // implementing base cases
    if (toX == x && toY == y) 
    return false;
    if (toX < 0 || toX > 7 || toY < 0 || toY > 7) 
    return false;
    if(board[toY][toX]!=nullptr && (board[toY][toX]->getColor()==this->getColor()))
    return false;

    // implementing every case
    if((abs(toX-x)==1 && abs(toY-y)==2) || (abs(toX-x)==2 && abs(toY-y)==1))
    {
        return true;
    }
    else
    {
        return false;
    }
}

Rook::Rook(char c, int x, int y) : Piece(c, x, y) {}

bool Rook::canMove(int toX, int toY, const ChessBoard<Piece*>& board)  
{
    // implementing base cases
    if (toX == x && toY == y) 
    return false;
    if (toX != x && toY != y) 
    return false;
    if (toX < 0 || toX > 7 || toY < 0 || toY > 7) 
    return false;
    if(board[toY][toX]!=nullptr && (board[toY][toX]->getColor()==this->getColor()))
    return false;

    // implementing every case
    if(toX == x)
    {
        int curY = y;
        if(toY>y)
        {
            curY = y + 1;
            while(toY!=curY)
            {                
                if(board[curY][x]!=nullptr)
                {
                    curY = -1;
                    break;
                }
                curY++;
            }
        }
        else
        {
            curY = y - 1;
            while(toY!=curY)
            {
                if(board[curY][x]!=nullptr)
                {
                    curY = -1;
                    break;
                }
                curY--;
            }
        }
        if(curY==toY)
        return true;
        else
        return false;
    }
    else
    {
        int curX = x;
        if(toX>x)
        {
            curX = x + 1;
            while(toX!=curX)
            {                
                if(board[y][curX]!=nullptr)
                {
                    curX = -1;
                    break;
                }
                curX++;
            }
        }
        else
        {
            curX = x - 1;
            while(toX!=curX)
            {
                if(board[y][curX]!=nullptr)
                {
                    curX = -1;
                    break;
                }
                curX--;
            }
        }
        if(curX==toX)
        return true;
        else
        return false;
    }
}

Bishop::Bishop(char c, int x, int y) : Piece(c, x, y) {}

bool Bishop::canMove(int toX, int toY, const ChessBoard<Piece*>& board) 
{
    // implementing base cases
    if (toX == x && toY == y) 
    return false;
    if (toX < 0 || toX > 7 || toY < 0 || toY > 7) 
    return false;
    if(board[toY][toX]!=nullptr && (board[toY][toX]->getColor()==this->getColor()))
    return false;

    // implementing every case

    if (abs(toY - y) != abs(toX - x)) return false;

    int stepY = (toY > y) ? 1 : -1;
    int stepX = (toX > x) ? 1 : -1;

    int curY = y + stepY;
    int curX = x + stepX;
    while (curY != toY && curX != toX) {
        if (board[curY][curX] != nullptr) return false; 
        curY += stepY;
        curX += stepX;
    }

    return true;
}

Pawn::Pawn(char c, int x, int y) : Piece(c, x, y) {}

bool Pawn::canMove(int toX, int toY, const ChessBoard<Piece*>& board)  
{
    // implementing base cases
    if (toX == x && toY == y) 
    return false;
    if (toX < 0 || toX > 7 || toY < 0 || toY > 7) 
    return false;


    int direction = (this->color == 'W') ? -1 : 1;
    int startRow = (this->color == 'W') ? 6 : 1;

    if (toX == x && toY == y + direction) {
        return (board[toY][toX] == nullptr);
    }

    if (toX == x && toY == y + (2 * direction) && y == startRow) {
        return (board[y + direction][x] == nullptr && board[toY][toX] == nullptr);
    }

    if (abs(toX - x) == 1 && toY == y + direction) {
        return (board[toY][toX] != nullptr && board[toY][toX]->getColor() != this->color);
    }

    return false;
}

Queen::Queen(char c, int x, int y) : Piece(c, x, y) {}

bool Queen::canMove(int toX, int toY, const ChessBoard<Piece*>& board)  
{
    // implementing base cases
    if (toX == x && toY == y) 
    return false;
    if (toX < 0 || toX > 7 || toY < 0 || toY > 7) 
    return false;
    if(board[toY][toX]!=nullptr && (board[toY][toX]->getColor()==this->getColor()))
    return false;


    // implementing every case

    bool isStraight = (toX == x || toY == y);
    bool isDiagonal = (abs(toX - x) == abs(toY - y));

    if (!isStraight && !isDiagonal) return false;

    
    int stepX = (toX > x) ? 1 : (toX < x ? -1 : 0);
    int stepY = (toY > y) ? 1 : (toY < y ? -1 : 0);

    
    int curX = x + stepX;
    int curY = y + stepY;

    while (curX != toX || curY != toY) {
        if (board[curY][curX] != nullptr) {
            return false; 
        }
        curX += stepX;
        curY += stepY;
    }

    return true;
}

char King::getType() const
{
    return 'K';
}

char Queen::getType() const
{
    return 'Q';
}

char Pawn::getType() const
{
    return 'P';
}

char Knight::getType() const
{
    return 'N';
}

char Rook::getType() const
{
    return 'R';
}

char Bishop::getType() const
{
    return 'B';
}