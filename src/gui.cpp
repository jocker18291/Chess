#include <SFML/Graphics.hpp>
#include "board.hpp"
#include "ai.hpp"
#include <iostream>

const int TILE_SIZE = 80;

sf::Vector2i getTileFromMouse(int x, int y) {
    return {x / TILE_SIZE, y/TILE_SIZE};
}