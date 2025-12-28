#ifndef PIECE_H
#define PIECE_H
template <typename T> class ChessBoard;

class Piece
{
    protected:
    char color;
    int x;
    int y;
    public:
    Piece(char c, int x, int y);
    virtual bool canMove(int toX, int toY, const ChessBoard<Piece*>& board) = 0;
    virtual ~Piece() = default;
    char getColor() const;
    virtual char getType() const = 0;
    void setX(int n_x);
    void setY(int n_y);
    int getX() const;
    int getY() const;
};


#endif