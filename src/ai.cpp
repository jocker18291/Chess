#include "../include/ai.hpp"

int minimax(Board board, int depth, bool maximizingPlayer) {
    if(depth == 0 || board.isGameOver()) {
        return board.evaluate();
    }

    std::vector<Move> moves = board.getAllLegalMoves(board.isWhiteToMove());

    if(moves.empty()) {
        return board.evaluate();
    }

    if(maximizingPlayer) {
        int best = -100000;
        for(const Move& move : moves) {
            Board newBoard = board;
            newBoard.makeMove(move);
            int score = minimax(newBoard, depth - 1, false);
            best = std::max(best, score);
        }
        return best;
    } else {
        int best = 1000000;
        for (const Move& move : moves) {
            Board newBoard = board;
            newBoard.makeMove(move);
            int score = minimax(newBoard, depth - 1, true);
            best = std::min(best, score);
        }
        return best;
    }
}