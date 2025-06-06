#include "../include/board.hpp"
#include <iostream>

Board::Board() {
    init();
}

void Board::init() {
    std::string start[8] = {
        "rnbqkbnr",
        "pppppppp",
        "........",
        "........",
        "........",
        "........",
        "PPPPPPPP",
        "RNBQKBNR"
    };

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            board[i][j] = start[i][j];
        }
    }
}

void Board::print() const {
    std::cout << "  a b c d e f g h\n";
    for(int i = 0; i < 8; i++) {
        std::cout << 8 - i << ' ';
        for(int j = 0; j < 8; j++) {
            std::cout << board[i][j] << ' ';
        }
        std::cout << 8 - i << "\n";
    }
    std::cout << "  a b c d e f g h\n";
}

bool Board::makeMove(const std::string& move) {
    if(move.length() != 4)
        return false;
    
    int fromY = 8 - (move[1] - '0');
    int fromX = move[0] - 'a';
    int toY = 8 - (move[3] - '0');
    int toX = move[2] - 'a';

    if(fromX < 0 || fromX > 7 || fromY < 0 || fromY > 7 || toX < 0 || toX > 7 || toY < 0 || toY > 7)
        return false;
}