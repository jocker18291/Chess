#include <iostream>
#include "../include/board.hpp"

int main() {
    Board board;
    board.print();

    while(!board.isGameOver()) {
        std::string move;
        std::cout << (board.isWhiteToMove() ? "White's move: " : "Black's move: ") << "\n";
        std::cin >> move;
        if(!board.makeMove(move)) {
            std::cout << "Illegal!\n";
        }
        board.print();
    }
    
    std::cout << "Game is over!\n";
    return 0;
}