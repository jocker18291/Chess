#include "../include/ai.hpp"

int minimax(Board board, int depth, bool maximizingPlayer, int alpha, int beta) {
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
            newBoard.makeMove2(move);
            int score = minimax(newBoard, depth - 1, false, alpha, beta);
            best = std::max(best, score);
            alpha = std::max(alpha, best);
            if(beta <= alpha) {
                break;
            }
        }
        return best;
    } else {
        int best = 1000000;
        for (const Move& move : moves) {
            Board newBoard = board;
            newBoard.makeMove2(move);
            int score = minimax(newBoard, depth - 1, true, alpha, beta);
            best = std::min(best, score);
            beta = std::min(beta, best);
            if(beta <= alpha) {
                break;
            }
        }
        return best;
    }
}

Move findBestMove(Board board, int depth) {
    std::vector<Move> moves = board.getAllLegalMoves(board.isWhiteToMove());
    if(moves.empty()) {
        return Move{-1, -1, -1, -1};
    }
    
    Move bestMove = moves[0];
    int bestScore = board.isWhiteToMove() ? -100000 : 100000;

    for(const Move& move : moves) {
        Board newBoard = board;
        newBoard.makeMove2(move);
        int score = minimax(newBoard, depth - 1, !board.isWhiteToMove(), -100000, 100000);

        if(board.isWhiteToMove() && score > bestScore) {
            bestScore = score;
            bestMove = move;
        }

        else if(!board.isWhiteToMove() && score < bestScore) {
            bestScore = score;
            bestMove = move;
        }
    }
    return bestMove;
}