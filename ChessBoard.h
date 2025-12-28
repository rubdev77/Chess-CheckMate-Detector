#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <vector>
#include <string>
#include "Matrix.h"
#include "Pieces.h"

class Piece;

template <typename T>
class ChessBoard : public Matrix<T>
{
    public:
    ChessBoard() : Matrix<T>(8,8)
    {
    }
    ~ChessBoard()
    {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if (this->mat[i][j]) 
                delete (Piece*)this->mat[i][j];
    }
    void Clear();
    ChessBoard(ChessBoard && other);
    ChessBoard& operator=(ChessBoard && other);
    std::pair<int, int> findKing(char color);
    bool isAttack(int T_X, int T_Y, char At_color);
    bool isMoveSafe(int fromX, int fromY, int toX, int toY, char myColor);
    bool isCheckmate(char color);
    void loadBoard(std::vector<std::string> & board);
};



template <typename T>
void ChessBoard<T>::loadBoard(std::vector<std::string>& board) {
    for (int j = 0; j < 8; j++) {
        for (int i = 0; i < 8; i++) {
            char p = board[j][i];
            if (p == '.') {
                this->mat[j][i] = nullptr;
                continue;
            }
            char color = (isupper(p)) ? 'W' : 'B';
            char type = toupper(p);
            if (type == 'K') this->mat[j][i] = (T)new King(color, i, j);
            else if (type == 'Q') this->mat[j][i] = (T)new Queen(color, i, j);
            else if (type == 'R') this->mat[j][i] = (T)new Rook(color, i, j);
            else if (type == 'B') this->mat[j][i] = (T)new Bishop(color, i, j);
            else if (type == 'N') this->mat[j][i] = (T)new Knight(color, i, j);
            else if (type == 'P') this->mat[j][i] = (T)new Pawn(color, i, j);
        }
    }
}

template <typename T>
void ChessBoard<T>::Clear()
{
    for (int i = 0; i < this->n; i++)
        for (int j = 0; j < this->m; j++)
            this->mat[i][j] = nullptr;
}

template <typename T>
ChessBoard<T>::ChessBoard(ChessBoard<T> && other)
{
    this -> n = other.n;
    this -> m = other.m;
    this -> mat = other.mat;
    other.mat = nullptr;
    other.n = 0;
    other.m = 0;
}

template <typename T>
ChessBoard<T>& ChessBoard<T>::operator =(ChessBoard<T> && other)
{
    if(this!=&other)
    {
        for(int i = 0; i < this-> n; i++)
        {
            delete [] this->mat[i];
        }
        delete [] this->mat;
        this -> n = other.n;
        this -> m = other.m;
        this -> mat = other.mat;
        other.mat = nullptr;
        other.n = 0;
        other.m = 0;
    }
    return *this;
}

template <typename T>
std::pair<int, int> ChessBoard<T>::findKing(char color)
{
    for(int j = 0; j < 8; j++)
    {
        for(int i = 0; i < 8; i++)
        {
            Piece * p = (Piece*)this->mat[j][i];
            if( p!=nullptr && p->getColor()==color && p->getType()=='K')
            {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

template <typename T>
bool ChessBoard<T>::isAttack(int T_X, int T_Y, char At_color)
{
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            Piece* p = (Piece*)this->mat[y][x];
            if (!p || p->getColor() != At_color) continue;

            if (p->getType() == 'P')
            {
                int dir = (At_color == 'W') ? -1 : 1;
                if (abs(T_X - x) == 1 && T_Y == y + dir)
                    return true;
            }
            else
            {
                if (p->canMove(T_X, T_Y, *this))
                    return true;
            }
        }
    }
    return false;
}

template <typename T>
bool ChessBoard<T>::isMoveSafe(int fromX, int fromY, int toX, int toY, char myColor) {
    Piece* mover = (Piece*)this->mat[fromY][fromX];
    if (!mover) return false;

    Piece* captured = (Piece*)this->mat[toY][toX];

    this->mat[toY][toX] = (T)mover;
    this->mat[fromY][fromX] = nullptr;
    int oldX = mover->getX(), oldY = mover->getY();
    mover->setX(toX); mover->setY(toY); 

    auto kPos = findKing(myColor);
    char oppColor = (myColor == 'W') ? 'B' : 'W';
    bool safe = !isAttack(kPos.first, kPos.second, oppColor);

    this->mat[fromY][fromX] = (T)mover;
    this->mat[toY][toX] = (T)captured;
    mover->setX(oldX); mover->setY(oldY);

    return safe;
}

template <typename T>
bool ChessBoard<T>::isCheckmate(char color) {
    auto kPos = findKing(color);
    char oppColor = (color == 'W') ? 'B' : 'W';

    if (!isAttack(kPos.first, kPos.second, oppColor)) return false;

    for (int j = 0; j < 8; j++) {
        for (int i = 0; i < 8; i++) {
            Piece* p = (Piece*)this->mat[j][i];
            if (p != nullptr && p->getColor() == color) {
                for (int t_j = 0; t_j < 8; t_j++) {
                    for (int t_i = 0; t_i < 8; t_i++) {
                        if (p->canMove(t_i, t_j, *this)) {
                            if (isMoveSafe(i, j, t_i, t_j, color)) {
                                return false; 
                            }
                        }
                    }
                }
            }
        }
    }
    return true; 
}

#endif