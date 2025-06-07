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
}