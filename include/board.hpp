#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>
#include <vector>
#include <random>

struct Move {
        int fromX, fromY;
        int toX, toY;
    };

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
    std::vector<Move> getAllLegalMoves(bool white) const;
    bool makeMove(const Move& move);
    int evaluate() const;
    char getPiece(int y, int x) const;
    bool isSquareAttacked(int x, int y, bool byWhite) const;
    bool isKingInCheck(bool white) const;
    std::string getGameState() const;
};

#endif