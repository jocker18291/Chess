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
        return false;
    }

    int dy = toY - fromY;
    int dx = toX - fromX;

    bool validMove = false;

    if(tolower(piece) == 'p') {
        int direction = isWhitePiece ? -1 : 1;
        int startRow = isWhitePiece ? 6 : 1;

        if(dx == 0 && dy == direction && board[toY][toX] == '.') {
            validMove = true;
        }
        else if(dx == 0 && dy == 2 * direction && fromY == startRow && board[fromY + direction][fromX] == '.' && board[toY][toX] == '.') {
            validMove = true;
        }
        else if(abs(dx) == 1 && dy == direction && board[toY][toX] != '.' && (bool)isupper(board[toY][toX]) != isWhitePiece){
            validMove = true;
        }
    }
    else if (tolower(piece) == 'n') {
        if((abs(dx) == 2 && abs(dy) == 1) || (abs(dx) == 1 && abs(dy) == 2)) {
            if(board[toY][toX] == '.' || isupper(board[toY][toX]) != isWhitePiece) {
                validMove = true;
            }
        }
    }
    else if(tolower(piece) == 'r') {
        if(dx == 0 || dy == 0) {
            int stepX = (dx == 0) ? 0 : (dx > 0 ? 1 : -1);
            int stepY = (dy == 0) ? 0 : (dy > 0 ? 1 : -1);
            int x = fromX + stepX;
            int y = fromY + stepY;

            bool pathClear = true;
            while(x != toX || y != toY) {
                if(board[y][x] != '.') {
                    pathClear = false;
                    break;
                }
                x += stepX;
                y += stepY;
            }

            if(pathClear && (board[toY][toX] == '.' || (bool)isupper(board[toY][toX]) != isWhitePiece)) {
                validMove = true;
            }
        }
    }
    else if(tolower(piece) == 'b') {
        if(abs(dx) == abs(dy)) {
            int stepX = (dx > 0) ? 1 : -1;
            int stepY = (dy > 0) ? 1 : -1;
            int x = fromX + stepX;
            int y = fromY + stepY;

            bool pathClear = true;
            while(x != toX || y != toY) {
                if(board[y][x] != '.') {
                    pathClear = false;
                    break;
                }
                x += stepX;
                y += stepY;
            }

            if(pathClear && (board[toY][toX] == '.' || (bool)isupper(board[toY][toX]) != isWhitePiece)) {
                validMove = true;
            }
        }
    }
    else if(tolower(piece) == 'q') {
        if((dx == 0 && abs(dy) != 0) || (abs(dx) != 0 && dy == 0) || (abs(dy) == abs(dx))) {
            int stepX = (dx == 0) ? 0 : (dx > 0 ? 1 : -1);
            int stepY = (dy == 0) ? 0 : (dy > 0 ? 1 : -1);
            int x = fromX + stepX;
            int y = fromY + stepY;

            bool pathClear = true;
            while(x != toX || y != toY) {
                if(board[y][x] != '.') {
                    pathClear = false;
                    break;
                }
                x += stepX;
                y += stepY;
            }

            if(pathClear && (board[toY][toX] == '.' || (bool)isupper(board[toY][toX]) != isWhitePiece)) {
                validMove = true;
            }
        }
    }
    else if(tolower(piece) == 'k') {
        if(abs(dx) <= 1 && abs(dy) <= 1) {
            if(board[toY][toX] == '.' || (bool)isupper(board[toY][toX]) != isWhitePiece) {
                validMove = true;
            }
        }
    }

    if(validMove) {
        if(tolower(piece) == 'p' && (toY ==0 || toY == 7)) {
            board[toY][toX] = isWhitePiece ? 'Q' : 'q';
        } else {
            board[toY][toX] = board[fromY][fromX];
        }
        
        board[fromY][fromX] = '.';
        whiteToMove = !whiteToMove;
        return true;
    }

    return false;
}

bool Board::isGameOver() const {
    std::vector<Move> legal = getAllLegalMoves(whiteToMove);
    if(!legal.empty()) return false;

    return isKingInCheck(whiteToMove);
}

bool Board::isWhiteToMove() const {
    return whiteToMove;
}

bool Board::makeMove2(const Move& move) {
    std::string moveStr;
    moveStr += ('a' + move.fromX);
    moveStr += ('8' - move.fromY);
    moveStr += ('a' + move.toX);
    moveStr += ('8' - move.toY);
    return makeMove(moveStr);
}

std::vector<Move> Board::getAllLegalMoves(bool white) const {
    std::vector<Move> moves;

    for(int y = 0; y < 8; y++) {
        for(int x = 0; x < 8; x++) {
            char piece = board[y][x];
            if(piece == '.' || isupper(piece) != white) {
                continue;
            }

            for(int ty = 0; ty < 8; ty++) {
                for(int tx = 0; tx < 8; tx++) {
                    std::string testMove;
                    testMove += ('a' + x);
                    testMove += ('8' - y);
                    testMove += ('a' + tx);
                    testMove += ('8' - ty);

                    Board test = *this;
                    if(test.makeMove(testMove)) {
                        moves.push_back({x, y, tx, ty});
                    }
                }
            }
        }
    }

    return moves;
}

int Board::evaluate() const {
    int score = 0;
    for(int y = 0; y < 8; y++) {
        for(int x = 0; x < 8; x++) {
            char p = board[y][x];
            switch(tolower(p)) {
                case 'p': score += (isupper(p) ? 10 : -10); break;
                case 'n': score += (isupper(p) ? 30 : -30); break;
                case 'b': score += (isupper(p) ? 30 : -30); break;
                case 'r': score += (isupper(p) ? 50 : -50); break;
                case 'q': score += (isupper(p) ? 90 : -90); break;
                case 'k': score += (isupper(p) ? 900 : -900); break;
            }
        }
    }
    return score;
}

char Board::getPiece(int y, int x) const {
    return board[y][x];
}

bool Board::isSquareAttacked(int x, int y, bool byWhite) const {
    for(int j = 0; j < 8; j++) {
        for(int i = 0; i < 8; i++) {
            char p = board[j][i];
            if(p == '.' || (bool)isupper(p) != byWhite)
                continue;
            
                std::string testMove;
                testMove += ('a' + i);
                testMove += ('8' - j);
                testMove += ('a' + x);
                testMove += ('8' - y);

                Board copy = *this;
                if(copy.makeMove(testMove))
                    return true;
        }
    }
    return false;
}

bool Board::isKingInCheck(bool white) const {
    for(int y = 0; y < 8; y++) {
        for(int x = 0; x < 8; x++) {
            char p = board[y][x];
            if(p == (white ? 'K' : 'k')) {
                return isSquareAttacked(x, y, !white);
            }
        }
    }
    return false;
}