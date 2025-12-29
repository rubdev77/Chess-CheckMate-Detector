#ifndef CHESSBOARD_H
#define CHESSBOARD_H


#include "Matrix.h"


class Piece;

template <typename T>
class ChessBoard : public Matrix<T>
{
    public:
    ChessBoard() : Matrix<T>(8,8)
    {
    }
    ~ChessBoard();
    void Clear();
    ChessBoard(ChessBoard && other);
    ChessBoard& operator=(ChessBoard && other);
    void loadBoard(std::vector<std::string> & board);
    std::pair<int, int> findKing(char color);
    bool canReachTargetSquare(int T_X, int T_Y, char At_color);
    bool isMoveSafe(int fromX, int fromY, int toX, int toY, char myColor);
    bool isCheckmate(char color);
};


template <typename T>
void ChessBoard<T>::Clear()
{
    for (int i = 0; i < this->n; i++)
        for (int j = 0; j < this->m; j++)
            this->mat[i][j] = nullptr;
}

template <typename T>
ChessBoard<T>::~ChessBoard()
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(this->mat[i][j]!=nullptr)
            delete this->mat[i][j];
        }
    }
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

// checks whether can a piece reach square with coordinates T_X, T_Y
template <typename T>
bool ChessBoard<T>::canReachTargetSquare(int T_X, int T_Y, char Attacker_color)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Piece* p = (Piece*)this->mat[i][j];
            if (!p || p->getColor() != Attacker_color) 
            continue;

            if (p->getType() == 'P')
            {
                int dir = (Attacker_color == 'W') ? -1 : 1;
                if (abs(T_X - j) == 1 && T_Y == i + dir)
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

// iterates through the board to find the king position and stores it in std::pait and returns it
template <typename T>
std::pair<int, int> ChessBoard<T>::findKing(char color)
{
    for(int j = 0; j < 8; j++)
    {
        for(int i = 0; i < 8; i++)
        {
            Piece * p = (Piece*)this->mat[j][i];
            if(p!=nullptr && p->getColor()==color && p->getType()=='K')
            {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}
// verifies if the move is legal or not
template <typename T>
bool ChessBoard<T>::isMoveSafe(int fromX, int fromY, int toX, int toY, char myColor) 
{

    Piece* mover = (Piece*)this->mat[fromY][fromX];
    Piece* captured = (Piece*)this->mat[toY][toX];

    if(!mover) 
    {
        return false;
    }

    this->mat[toY][toX] = (T)mover;
    this->mat[fromY][fromX] = nullptr;

    int oldX = mover->getX();
    int oldY = mover->getY();

    mover->setX(toX);
    mover->setY(toY); 

    std::pair<int, int> king_Pos = findKing(myColor);
    char oppColor = (myColor == 'W') ? 'B' : 'W';
    bool safe = !(canReachTargetSquare(king_Pos.first, king_Pos.second, oppColor));

    this->mat[fromY][fromX] = (T)mover;
    this->mat[toY][toX] = (T)captured;
    mover->setX(oldX); 
    mover->setY(oldY);

    return safe;
}

// checks whether there is a checkmate
template <typename T>
bool ChessBoard<T>::isCheckmate(char color) 
{

    std::pair <int, int> king_Pos = findKing(color);

    char oppColor;

    if(color=='W')
    {
    oppColor = 'B';
    }
    else
    {
    oppColor = 'W';
    }

    if (!canReachTargetSquare(king_Pos.first, king_Pos.second, oppColor)) 
    {
        return false;
    }

    for (int j = 0; j < 8; j++) {
        for (int i = 0; i < 8; i++) {
            Piece* p = (Piece*)this->mat[j][i];
            if (p != nullptr && p->getColor() == color)
            {
                for (int to_j = 0; to_j < 8; to_j++)
                {
                    for (int to_i = 0; to_i < 8; to_i++) 
                    {
                        if (p -> canMove(to_i, to_j, *this)) 
                        {
                            if (isMoveSafe(i, j, to_i, to_j, color)) 
                            {
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

template <typename T>
void ChessBoard<T>::loadBoard(std::vector<std::string>& board) {
    for (int j = 0; j < 8; j++) {
        for (int i = 0; i < 8; i++) 
        {
            char piece = board[j][i];
            if (piece == '.') 
            {
                this->mat[j][i] = nullptr;
                continue;
            }
            char color;
            if(isupper(piece))
            {
                color = 'W';
            }
            else
            {
                color = 'B';
            }
            char type = toupper(piece);
            switch(type)
            {
            case 'K':
            this->mat[j][i] = (T)new King(color, i, j);
            break;
            case 'Q':
            this->mat[j][i] = (T)(new Queen(color, i, j));
            break;
            case 'R':
            this->mat[j][i] = (T)(new Rook(color, i, j));
            break;
            case 'B':
            this->mat[j][i] = (T)(new Bishop(color, i, j));
            break;
            case 'N':
            this->mat[j][i] = (T)(new Knight(color, i, j));
            break;
            case 'P':
            this->mat[j][i] = (T)(new Pawn(color, i, j));
            break;
            default:
                break;
            }
        }
    }
}

#endif