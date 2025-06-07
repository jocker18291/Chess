#include <SFML/Graphics.hpp>
#include "../include/board.hpp"
#include "../include/ai.hpp"
#include <iostream>

const int TILE_SIZE = 80;

sf::Vector2i getTileFromMouse(int x, int y) {
    return {x / TILE_SIZE, y/TILE_SIZE};
}

int main() {
    sf::RenderWindow window(sf::VideoMode(8 * TILE_SIZE, 8 * TILE_SIZE), "Chess");
    Board board;

    std::map<std::string, sf::Texture> textures;
    std::map<char, std::string> figureMap = {
        {'P', "w_piece"}, {'R', "rw_piece"}, {'N', "nw_piece"}, {'B', "bw_piece"}, {'Q', "qw_piece"}, {'K', "kw_piece"},
        {'p', "piece"}, {'r', "r_piece"}, {'n', "n_piece"}, {'b', "b_piece"}, {'q', "q_piece"}, {'k', "k_piece"}
    };

    for(auto& [symbol, name] : figureMap) {
        sf::Texture tex;
        if (!tex.loadFromFile("res/" + name + ".png")) {
            std::cerr << "Lack of texture: " << name << ".png\n";
        }
        textures[name] = tex;
    }

    sf::Vector2i selected = {-1, 1};

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::MouseButtonPressed) {
                auto [x, y] = getTileFromMouse(event.mouseButton.x, event.mouseButton.y);
                if(selected.x == -1) {
                    selected = {x, y};
                } else {
                    std::string move;
                    move += ('a' + selected.x);
                    move += ('8' - selected.y);
                    move += ('a' + x);
                    move += ('8' - y);

                    if(board.makeMove(move)) {
                        std::cout << "Move: " << move << std::endl;

                        if(!board.isWhiteToMove()) {
                            Move aiMove = findBestMove(board, 3);
                            board.makeMove(aiMove);
                        }
                    }

                    selected = {-1, 1};
                }
            }
        }
    }
}