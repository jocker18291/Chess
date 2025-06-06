#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>

class Board {
private:
    char board[8][8];
    bool whiteToMove;

public:
    Board();
    void init();
    void print() const;
    bool makeMove(const std::string& move);
    bool isGameOver() const;
    bool isWhiteToMove() const;
};

#endif