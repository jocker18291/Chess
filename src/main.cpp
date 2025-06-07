#include <iostream>
#include "../include/board.hpp"
#include "../include/ai.hpp"

int main() {
    Board board;
    board.print();

    while(!board.isGameOver()) {
        std::string move;
        if(board.isWhiteToMove()) {
            std::cout << "White's turn: ";
            std::cin >> move;
            if(!board.makeMove(move)) {
                std::cout << "Illegal!\n";
            }
            board.print();
            std::cout << std::endl;
        } else {
            Move move = findBestMove(board, 18);
            board.makeMove(move);
            board.print();
        }
    }
    
    std::cout << "Game is over!\n";
    return 0;
}