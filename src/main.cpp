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
            std::vector<Move> aiMoves = board.getAllLegalMoves(false);
            if(!aiMoves.empty()) {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(0, aiMoves.size() - 1);

                Move aiMove = aiMoves[dis(gen)];
                board.makeMove(aiMove);
                board.print();
                std::cout << std::endl;
            } else {
                std::cout << "No legal moves left!";
                break;
            }
        }
    }
    
    std::cout << "Game is over!\n";
    return 0;
}