#ifndef PIECES_H
#define PIECES_H
#include "Piece.h"


template <typename T> class ChessBoard;

class King : public Piece
{
    public:
    bool canMove(int toX, int toY, const ChessBoard<Piece*>& board) override;
    King(char c, int x, int y);
    char getType() const override;
};


template <typename T> class ChessBoard;
class Queen : public Piece
{
    public:
    Queen(char c, int x, int y);
    bool canMove(int toX, int toY, const ChessBoard<Piece*>& board) override;
    char getType() const override;
};

template <typename T> class ChessBoard;
class Rook : public Piece
{
    public:
    Rook(char c, int x, int y);
    bool canMove(int toX, int toY, const ChessBoard<Piece*>& board) override;
    char getType() const override;
};

template <typename T> class ChessBoard;
class Bishop : public Piece
{
    public:
    Bishop(char c, int x, int y);
    bool canMove(int toX, int toY, const ChessBoard<Piece*>& board) override;
    char getType() const override;
};

template <typename T> class ChessBoard;
class Knight : public Piece
{
    public:
    Knight(char c, int x, int y);
    bool canMove(int toX, int toY, const ChessBoard<Piece*>& board) override;
    char getType() const override;
};

template <typename T> class ChessBoard;
class Pawn : public Piece
{
    public:
    Pawn(char c, int x, int y);
    bool canMove(int toX, int toY, const ChessBoard<Piece*>& board) override;
    char getType() const override;
};

#endif