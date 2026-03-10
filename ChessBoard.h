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
    bool isMateInOne(char color);
    bool isMateInTwo(char color);
    bool isBoardLegal(char currentTurnColor);
    bool isStalemate(char color);
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

template <typename T>
bool ChessBoard<T>::isBoardLegal(char currentTurnColor)
{
    int w_kings = 0;
    int b_kings = 0;
    std::pair<int, int> w_pos = {-1, -1};
    std::pair<int, int> b_pos = {-1, -1};

    for (int y = 0; y < 8; y++) 
    {
        for (int x = 0; x < 8; x++) 
        {
            Piece* p = (Piece*)this->mat[y][x];

            if (!p) 
            {
                continue;
            }

            if (p->getType() == 'K') 
            {
                if (p->getColor() == 'W') 
                {
                    w_kings++;
                    w_pos = {x, y};
                }
                else 
                {
                    b_kings++;
                    b_pos = {x, y};
                }
            }
        }
    }

    if (w_kings != 1 || b_kings != 1) 
    {
        return false;
    }

    if (abs(w_pos.first - b_pos.first) <= 1 && abs(w_pos.second - b_pos.second) <= 1) 
    {
        return false;
    }

    char oppColor = (currentTurnColor == 'W') ? 'B' : 'W';
    std::pair<int, int> oppKing = (oppColor == 'W') ? w_pos : b_pos;

    if (canReachTargetSquare(oppKing.first, oppKing.second, currentTurnColor)) 
    {
        return false;
    }

    return true;
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
bool ChessBoard<T>::isStalemate(char color)
{
    
    if (canReachTargetSquare(findKing(color).first, findKing(color).second, 
        (color == 'W' ? 'B' : 'W'))) 
    {
        return false; 
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



template <typename T>
bool ChessBoard<T>::isMateInOne(char color)
{
    char oppColor = (color == 'W') ? 'B' : 'W';

    if (!isBoardLegal(color)) 
    {
        return false;
    }

    for (int y = 0; y < 8; y++) 
    {
        for (int x = 0; x < 8; x++) 
        {

            Piece* p = this->mat[y][x];
            if (!p || p->getColor() != color) 
            continue;

            for(int ty = 0; ty < 8; ty++) 
            {
                for (int tx = 0; tx < 8; tx++)
                {

                    if(!p->canMove(tx, ty, *this))
                    continue;

                    if(!isMoveSafe(x, y, tx, ty, color))
                    continue;

                    Piece* captured = this->mat[ty][tx];

                    int oldX = p->getX();
                    int oldY = p->getY();

                    this->mat[ty][tx] = p;
                    this->mat[y][x] = nullptr;
                    p->setX(tx);
                    p->setY(ty);

                    bool mate = isCheckmate(oppColor);

                    p->setX(oldX);
                    p->setY(oldY);
                    this->mat[y][x] = p;
                    this->mat[ty][tx] = captured;

                    if(mate)
                    return true;
                }
            }
        }
    }
    return false;
}


template <typename T>
bool ChessBoard<T>::isMateInTwo(char color)
{

    if (isStalemate(color))
    return false;

    
    char opp = (color == 'W') ? 'B' : 'W';

    if (!isBoardLegal(color)) 
    {
        return false;
    }

    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            Piece* p = (Piece*)this->mat[y][x];
            if (!p || p->getColor() != color)
                continue;

            for (int ty = 0; ty < 8; ty++)
            {
                for (int tx = 0; tx < 8; tx++)
                {
                    if (!p->canMove(tx, ty, *this))
                        continue;

                    if (!isMoveSafe(x, y, tx, ty, color))
                        continue;

                    Piece* cap1 = (Piece*)this->mat[ty][tx];
                    int ox = p->getX();
                    int oy = p->getY();

                    this->mat[ty][tx] = (T)p;
                    this->mat[y][x] = nullptr;
                    p->setX(tx);
                    p->setY(ty);

                    bool forcedMate = true;
                    bool opponentHasMove = false;

                    for (int y2 = 0; y2 < 8 && forcedMate; y2++)
                    {
                        for (int x2 = 0; x2 < 8 && forcedMate; x2++)
                        {
                            Piece* p2 = (Piece*)this->mat[y2][x2];
                            if (!p2 || p2->getColor() != opp)
                                continue;

                            for (int ty2 = 0; ty2 < 8 && forcedMate; ty2++)
                            {
                                for (int tx2 = 0; tx2 < 8; tx2++)
                                {
                                    if (!p2->canMove(tx2, ty2, *this))
                                        continue;

                                    if (!isMoveSafe(x2, y2, tx2, ty2, opp))
                                        continue;

                                    opponentHasMove = true;

                                    Piece* cap2 = (Piece*)this->mat[ty2][tx2];
                                    int ox2 = p2->getX();
                                    int oy2 = p2->getY();

                                    this->mat[ty2][tx2] = (T)p2;
                                    this->mat[y2][x2] = nullptr;
                                    p2->setX(tx2);
                                    p2->setY(ty2);

                                    if (!isMateInOne(color))
                                    {
                                        forcedMate = false;
                                    }

                                    this->mat[y2][x2] = (T)p2;
                                    this->mat[ty2][tx2] = (T)cap2;
                                    p2->setX(ox2);
                                    p2->setY(oy2);

                                    if (!forcedMate)
                                        break;
                                }
                            }
                        }
                    }

                    this->mat[y][x] = (T)p;
                    this->mat[ty][tx] = (T)cap1;
                    p->setX(ox);
                    p->setY(oy);

                    if ((opponentHasMove || !opponentHasMove) && forcedMate)
                        return true;
                }
            }
        }
    }

    return false;
}




#endif