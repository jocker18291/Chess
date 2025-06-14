#ifndef AI_HPP
#define AI_HPP

#include "board.hpp"

int minimax(Board board, int depth, bool maximizingPlayer, int alpha, int beta);
Move findBestMove(Board board, int depth);

#endif