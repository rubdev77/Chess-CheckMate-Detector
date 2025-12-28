#include "Piece.h"

Piece::Piece(char c, int x, int y) : color(c), x(x), y(y) { }

char Piece::getColor() const
{
   return this->color; 
}

void Piece::setX(int n_x)
{
   x = n_x;
}

void Piece::setY(int n_y)
{
   y = n_y;
}

int Piece::getX() const
{
   return x;
}

int Piece::getY() const
{
   return y;
}