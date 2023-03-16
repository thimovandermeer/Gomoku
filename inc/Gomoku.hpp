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
#include "ValidatorContainer.hpp"

#define BOARD_SIZE 19

class IValidator;

class IValidatorContainer;

class Gomoku {
public:
    Gomoku() = delete;
    Gomoku(const Gomoku&) = delete;
    Gomoku& operator=(const Gomoku&) = delete;
    ~Gomoku() = default;
    Gomoku(std::unique_ptr<IValidatorContainer>& validatorContainer, std::unique_ptr<IGraphics>& graphics) :
            _validatorContainer(std::move(validatorContainer)), _graphics(std::move(graphics)),
            _board({BOARD_SIZE, {BOARD_SIZE, Tile::EMPTY}}), _player(Player::PLAYERONE), _state{} {}

    void gameLoop();

private:
    std::unique_ptr<IValidatorContainer> _validatorContainer;
    std::unique_ptr<IGraphics> _graphics;
    std::vector<std::vector<Tile>> _board;
    Player _player;
    State _state;
    void doMove(const sf::Vector2<int>& moveLocation);
    void validateMove(Coordinate coords, std::stringstream& ss);
    void handleMouseButtonPressed(const sf::Event& event);
    void handleKeyPressed(const sf::Event& event);
};


#endif //GOMOKU_GOMOKU_HPP
