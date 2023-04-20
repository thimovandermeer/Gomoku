//
// Created by Jonas Bennink Bolt on 2/3/23.
//

#ifndef GOMOKU_GOMOKU_HPP
#define GOMOKU_GOMOKU_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "Graphics.hpp"
#include "types.hpp"
#include "Ai.hpp"

#define DEBUG_STONE_COORDINATES


class IValidator;

class IGraphics;

class IAi;

#define BOARD_SIZE 19

typedef std::function<void(sf::Vector2i&)> move_f;

class Gomoku {
public:
    Gomoku() = delete;
    Gomoku(const Gomoku&) = delete;
    Gomoku& operator=(const Gomoku&) = delete;
    ~Gomoku() = default;
    Gomoku(std::unique_ptr<IGraphics>& graphics, std::unique_ptr<IAi>& ai) : _graphics(std::move(graphics)),
                                                                             _ai(std::move(ai)), _board({BOARD_SIZE,
                                                                                                         {BOARD_SIZE,
                                                                                                          Tile::EMPTY}}),
                                                                             _player(Player::PLAYERONE),
                                                                             _gameEnd(false), _captures{0, 0},
                                                                             _capturedCoords{},
                                                                             _gameType(GameType::INVALID) {
        _moveDirections.emplace_back([](sf::Vector2i& v) { --v.x; }, [](sf::Vector2i& v) { ++v.x; });
        _moveDirections.emplace_back([](sf::Vector2i& v) { --v.y; }, [](sf::Vector2i& v) { ++v.y; });
        _moveDirections.emplace_back([](sf::Vector2i& v) { --v.x; --v.y; }, [](sf::Vector2i& v) { ++v.x; ++v.y; });
        _moveDirections.emplace_back([](sf::Vector2i& v) { --v.x; ++v.y; }, [](sf::Vector2i& v) { ++v.x; --v.y; });
    }

    void gameLoop();

private:
    std::unique_ptr<IGraphics> _graphics;
    std::unique_ptr<IAi> _ai;
    std::vector<std::vector<Tile>> _board;
    Player _player;
    bool _gameEnd;
    std::pair<int, int> _captures;
    std::vector<std::pair<sf::Vector2i, sf::Vector2i>> _capturedCoords;
    std::vector<std::pair<move_f, move_f>> _moveDirections;
    GameType _gameType;

    void handleKeyPressed(const sf::Event& event);
    void handleMouseButtonPressed(const sf::Event& event);
    void doMove(const sf::Vector2<int>& moveLocation);
    bool validateMove();
    void capture(const sf::Vector2i& moveLocation);
    void findCapture(const sf::Vector2i& moveLocation);
    bool findCaptureInDirection(const move_f& move, const sf::Vector2i& moveLocation);
    void undoCapture();
    Coordinate aiMove();

    bool canBeCapturedInDirection(
            const std::pair<move_f, move_f>& dir,
            const sf::Vector2i& location) const;
    bool canBeCaptured(const sf::Vector2i& location) const;
    bool hasGameEnded(const sf::Vector2i& placedStone) const;
};


#endif //GOMOKU_GOMOKU_HPP
