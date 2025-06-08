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

    bool gameOver = false;
    sf::Font font;
    sf::Text resultText;
    if(!font.loadFromFile("res/arial.ttf")) {
        std::cerr << "Lack of font\n";
    }

    resultText.setFont(font);
    resultText.setCharacterSize(36);
    resultText.setFillColor(sf::Color::Red);
    resultText.setStyle(sf::Text::Bold);
    resultText.setPosition(50, 8 * TILE_SIZE /2 - 30);

    sf::Vector2i selected = {-1, -1};

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::MouseButtonPressed) {
                auto [x, y] = getTileFromMouse(event.mouseButton.x, event.mouseButton.y);
                if(gameOver) continue;
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
                            Move aiMove = findBestMove(board, 18);
                            std::string aiMoveStr;
                            aiMoveStr += ('a' + aiMove.fromX);
                            aiMoveStr += ('8' - aiMove.fromY);
                            aiMoveStr += ('a' + aiMove.toX);
                            aiMoveStr += ('8' - aiMove.toY);
                            board.makeMove(aiMove);
                            std::cout << "AI Move: " << aiMoveStr << std::endl;
                        }
                        if(board.isGameOver()) {
                            gameOver = true;
                            resultText.setString(board.getGameState());
                        }
                    }

                    selected = {-1, -1};
                }
            }
        }

        window.clear();
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                sf::RectangleShape tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                tile.setPosition(i * TILE_SIZE, j * TILE_SIZE);
                tile.setFillColor((i + j) % 2 ? sf::Color(240, 217, 181) : sf::Color(181,136, 99));
                window.draw(tile);

                char piece = board.getPiece(j, i);
                if (piece != '.' && figureMap.count(piece)) {
                    sf::Sprite sprite(textures[figureMap[piece]]);
                    sprite.setScale(
                        TILE_SIZE / sprite.getTexture()->getSize().x,
                        TILE_SIZE / sprite.getTexture()->getSize().y
                    );

                    sprite.setOrigin(
                        sprite.getTexture()->getSize().x /2.f,
                        sprite.getTexture()->getSize().y / 2.f
                    );
                    sprite.setPosition(i * TILE_SIZE + TILE_SIZE /2, j * TILE_SIZE + TILE_SIZE /2);
                    window.draw(sprite);
                }
            }
        }
        if(gameOver) {
            window.draw(resultText);
        }
        window.display();
    }

    return 0;
}