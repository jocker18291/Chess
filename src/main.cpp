#include <iostream>
#include "../include/board.hpp"

int main() {
    Board board;
    board.print();

    std::string move;
    std::cout << "Move: ";
    std::cin >> move;
    if(!board.makeMove(move)) {
        std::cout << "Illegal!\n";
    }
    board.print();

    return 0;
}