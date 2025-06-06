#include "board.hpp"
#include <iostream>

Board::Board() {
    init();
}

void Board::init() {
    std::string start[8] = {
        "rnbqkbnr";
        "pppppppp";
        "........";
        "........";
        "........";
        "........";
        "PPPPPPPP";
        "RNBQKBNR";
    };

    for(int i - 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            board[i][j] = start[i][j];
        }
    }
}

void Board::print() const {
    std::cout << "  a b c d e f g h\n";
    for(int i = 0; i < 9; i++) {
        std::cout << 8 - i << ' ';
        for(int j = 0; j < 8; j++) {
            std::cout << board[i][j] << ' ';
        }
        std::cout << 8 - i << "\n";
    }
    std::cout << "  a b c d e f g h\n";
}