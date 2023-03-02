//
// Created by Jonas Bennink Bolt on 2/3/23.
//

#ifndef GOMOKU_GOMOKU_HPP
#define GOMOKU_GOMOKU_HPP

#include <vector>
#include "Validator.hpp"
#include "Graphics.hpp"
#include <SFML/Graphics.hpp>

#define BOARD_SIZE 19

enum class Tile {
    P1, P2, EMPTY
};

class Gomoku {
public:
    Gomoku() = delete;
    Gomoku(const Gomoku&) = delete;
    Gomoku& operator=(const Gomoku&) = delete;
    ~Gomoku() = default;
    Gomoku(std::unique_ptr<IValidator>& validator, std::unique_ptr<IGraphics>& graphics) :
            _validator(std::move(validator)), _graphics(std::move(graphics)),
            _board({BOARD_SIZE, {BOARD_SIZE, Tile::EMPTY}}) {}

    void gameLoop();

private:
    std::unique_ptr<IValidator> _validator;
    std::unique_ptr<IGraphics> _graphics;
    std::vector<std::vector<Tile>> _board;

    void doMove(const sf::Vector2<int>& moveLocation);
    void validateMove();
    void handleMouseButtonPressed(const sf::Event& event);
    void handleKeyPressed(const sf::Event& event);

};


#endif //GOMOKU_GOMOKU_HPP
