//
// Created by Jonas Bennink Bolt on 2/3/23.
//

#ifndef GOMOKU_GOMOKU_HPP
#define GOMOKU_GOMOKU_HPP

#include <vector>
#include "Validator.hpp"
#include "Graphics.hpp"
#include <SFML/Graphics.hpp>
#include "types.hpp"
#define BOARD_SIZE 19

class IValidator;
class Gomoku {
public:
    Gomoku() = delete;
    Gomoku(const Gomoku&) = delete;
    Gomoku& operator=(const Gomoku&) = delete;
    ~Gomoku() = default;
    Gomoku(std::unique_ptr<IValidator>& validator_p1, std::unique_ptr<IValidator>& validator_p2, std::unique_ptr<IGraphics>& graphics) :
            _validator_P1(std::move(validator_p1)), _validator_P2(std::move(validator_p2)),_graphics(std::move(graphics)),
            _board({BOARD_SIZE, {BOARD_SIZE, Tile::EMPTY}}) {}

    void gameLoop();

private:
    std::unique_ptr<IValidator>     _validator_P1;
    std::unique_ptr<IValidator>     _validator_P2;
    std::unique_ptr<IGraphics>      _graphics;
    std::vector<std::vector<Tile>>  _board;
    Player                          _player;
    void doMove(const sf::Vector2<int>& moveLocation);
    void validateMove(Coordinates coords, std::stringstream &ss);
    void handleMouseButtonPressed(const sf::Event& event);
    void handleKeyPressed(const sf::Event& event);
    void whichPlayer();
};


#endif //GOMOKU_GOMOKU_HPP
