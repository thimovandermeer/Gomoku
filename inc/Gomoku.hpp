//
// Created by Jonas Bennink Bolt on 2/3/23.
//

#ifndef GOMOKU_GOMOKU_HPP
#define GOMOKU_GOMOKU_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "Validator.hpp"
#include "Graphics.hpp"
#include "types.hpp"

#define DEBUG_STONE_COORDINATES

#define BOARD_SIZE 19

class IValidator;
class IGraphics;

class Gomoku {
public:
    Gomoku() = delete;
    Gomoku(const Gomoku&) = delete;
    Gomoku& operator=(const Gomoku&) = delete;
    ~Gomoku() = default;
    Gomoku(std::unique_ptr<IValidator> &validator, std::unique_ptr<IGraphics>& graphics) :
			_validator(std::move(validator)), _graphics(std::move(graphics)),
			_board({BOARD_SIZE, {BOARD_SIZE, Tile::EMPTY}}), _player(Player::PLAYERTWO), _state{}, _gameEnd(false),
			_p1Captures(0), _p2Captures(0) {}

    void gameLoop();

private:
    std::unique_ptr<IValidator> _validator;
    std::unique_ptr<IGraphics> _graphics;
    std::vector<std::vector<Tile>> _board;
    Player _player;
    State _state;
    bool _gameEnd;
    int _p1Captures;
    int _p2Captures;
    void handleKeyPressed(const sf::Event& event);
    void handleMouseButtonPressed(const sf::Event& event);
    void doMove(const sf::Vector2<int>& moveLocation);
    void validateMove(Coordinate coords);
    bool hasGameEnded(const sf::Vector2i& placedStone) const;
};


#endif //GOMOKU_GOMOKU_HPP
