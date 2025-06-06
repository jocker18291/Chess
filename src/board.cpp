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

    whiteToMove = true;
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

    char piece = board[fromY][fromX];
    if(piece == '.')
        return false;

    bool isWhitePiece = isupper(piece);

    if(isWhitePiece != whiteToMove) {
        std::cout << "Cannot move opponent's piece!\n";
        return false;
    }

    int dy = toY - fromY;
    int dx = toX - fromX;

    if(tolower(piece) == 'p') {
        int direction = isWhitePiece ? -1 : 1;
        int startRow = isWhitePiece ? 6 : 1;

        if(dx == 0 && dy == direction && board[toY][toX] == '.') {
            board[toY][toX] = board[fromY][fromX];
            board[fromY][fromX] = '.';
        }

        else if(dx == 0 && dy == 2 * direction && fromY == startRow && board[fromY + direction][fromX] == '.' && board[toY][toX] == '.') {
            board[toY][toX] = board[fromY][fromX];
            board[fromY][fromX] = '.';
        }

        else if(abs(dx) == 1 && dy == direction && board[toY][toX] != '.' && isupper(board[toY][toX] != isWhitePiece)){
            board[toY][toX] = board[fromY][fromX];
            board[fromY][fromX] = '.';
        }
        
        else {
            std::cout << "Illegal move!\n";
            return false;
        }
    }

    
    
    whiteToMove = !whiteToMove;
    return true;
}

bool Board::isGameOver() const {
    return false;
}

bool Board::isWhiteToMove() const {
    return whiteToMove;
}