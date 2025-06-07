#include "../include/ai.hpp"

int minimax(Board board, int depth, bool maximizingPlayer) {
    if(depth == 0 || board.isGameOver()) {
        return board.evaluate();
    }
}