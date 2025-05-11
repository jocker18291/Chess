#ifndef PIECE_HPP
#define PIECE_HPP

class Piece {
private:
    char type;
    char color;
public:
    Piece(char type, char color);
    bool canMoveTo();
}

#endif