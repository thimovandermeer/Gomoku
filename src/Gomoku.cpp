//
// Created by Jonas Bennink Bolt on 2/3/23.
//

#include <SFML/Graphics.hpp>
#include <functional>
#include <fmt/core.h>
#include "logger.hpp"
#include "types.hpp"
#include "Gomoku.hpp"
#include "NewValidator.hpp"

void Gomoku::handleKeyPressed(const sf::Event& event) {
    if (event.key.code == sf::Keyboard::Key::Escape) {
        if (_graphics->getRulesActive()) {
            _graphics->setRulesActive(false);
            _graphics->update(_board, _p1Captures, _p2Captures);
        } else {
            _graphics->closeWindow();
        }
    }
}

void Gomoku::handleMouseButtonPressed(const sf::Event& event) {
    if (event.mouseButton.button == sf::Mouse::Right) {
        LOG("Right click at (%d, %d)", event.mouseButton.x, event.mouseButton.y);
        return;
    }
    if (_graphics->isRulesClick({event.mouseButton.x, event.mouseButton.y})) {
        // toggle rules
        _graphics->setRulesActive(not _graphics->getRulesActive());
        _graphics->update(_board, _p1Captures, _p2Captures);
        return;
    }
    if (_graphics->getRulesActive()) {
        LOG("rules page up, board not active");
        return;
    }
    auto moveLocation = _graphics->nearestIntersection(event.mouseButton.x, event.mouseButton.y);
    if (moveLocation == std::nullopt) {
        return;
    }
    doMove(moveLocation.value());
    if (_gameEnd) {
        _graphics->setHeader(fmt::format("Player {} has won!", static_cast<int>(_player) + 1));
    }
    // only redraw the board in this case because we don't change the board for other events
    _graphics->update(_board, _p1Captures, _p2Captures);
}

void Gomoku::gameLoop() {
    setLogLevel(LOG_WARN);
    // draw board for the first time
    _graphics->update(_board, _p1Captures, _p2Captures);
	// hack;
	while (true) {
        if (not _graphics->isWindowOpen()) {
            // potential cleanup, but essentially the window is closed, so we exit
            return;
        }
        if (_player == Player::PLAYERTWO) {
        // TODO: AI move here

//            WARN("before ai call");
//             ai call
//            Coordinate newMove = aiMove();
//             do move
//            WARN("after ai call");
//            if(newMove.y != -1 && newMove.x != -1) {
//                sf::Vector2<int> move;
//                move.y = newMove.y;
//                move.x = newMove.x;
//                WARN("We are going to do the move %i %i", move.y, move.x);
//                doMove({newMove.x, newMove.y});
//                // assuming AI always does a valid move, board can be udpated
//                _graphics->update(_board, _p1Captures, _p2Captures);
//            }
//            continue;
        }
        std::optional<sf::Event> eventWrapper = _graphics->getEvent();
        while (eventWrapper != std::nullopt) {
            sf::Event event = eventWrapper.value();
            switch (event.type) {
                case sf::Event::Closed: {
                    _graphics->closeWindow();
                    break;
                }
                case sf::Event::KeyPressed: {
                    handleKeyPressed(event);
                    break;
                }
                case sf::Event::MouseButtonPressed: {
                    if (not _gameEnd) {
                        handleMouseButtonPressed(event);
                    }
                    break;
                }
                default:
                    break;
            }

            eventWrapper = _graphics->getEvent();
        }
    }
}

void Gomoku::doMove(const sf::Vector2<int>& moveLocation) {
    if (_board[moveLocation.y][moveLocation.x] != Tile::EMPTY) {
        _graphics->setHeader(fmt::format("location not empty\n\tat ({}, {})", moveLocation.x, moveLocation.y));
        return;
    }
    if (_player == Player::PLAYERONE) {
		_board[moveLocation.y][moveLocation.x] = Tile::P1;
    } else {
        _board[moveLocation.y][moveLocation.x] = Tile::P2;
    }

    // TODO: do capture

    // probably this check will become part of the validator
    if (validateMove()) {
        // change _board to reflect new board state
        if (_state.capture) {
            Coordinate p = _state.capturePos.one;
            _board[p.y][p.x] = Tile::EMPTY;
            p = _state.capturePos.two;
            _board[p.y][p.x] = Tile::EMPTY;
            if (_player == Player::PLAYERONE) {
                ++_p1Captures;
            } else {
                ++_p2Captures;
            }
        }
        _gameEnd = hasGameEnded(moveLocation);
        _graphics->setHeader(fmt::format("placed stone\n\tat ({}, {})", moveLocation.x, moveLocation.y));

        _player = _player == Player::PLAYERONE ? Player::PLAYERTWO : Player::PLAYERONE;
    } else {
        // undo move that is not ok
        _board[moveLocation.y][moveLocation.x] = Tile::EMPTY;
        _graphics->setHeader(fmt::format("move creates 2 open threes\n\tat ({}, {})", moveLocation.x, moveLocation.y));
        // TODO: undo capture if necessary
    }
    // set header to whatever we want it to be
}

bool Gomoku::validateMove() {
//	_state = _validator->validate(_board, coords, _player);
    NewValidator validator(_board, _player);
    return validator.validate();
}

static bool isCorrectTile(const std::vector<std::vector<Tile>>& board, const sf::Vector2i& pos, const Tile& val) {
    return board[pos.y][pos.x] == val;
}

static bool isInBounds(const sf::Vector2i& pos) {
    return pos.x >= 0 && pos.x < BOARD_SIZE && pos.y >= 0 && pos.y < BOARD_SIZE;
}

static int totalInDirection(const std::vector<std::vector<Tile>>& board, const std::function<void(sf::Vector2i&)>& move,
                            const sf::Vector2i& start, const Tile& val) {
    sf::Vector2i checkPos = start;
    int ret = 0;
    for (int i = 0; i < 4; ++i) {
        move(checkPos);
        if (not isInBounds(checkPos) || not isCorrectTile(board, checkPos, val)) {
            return ret;
        }
        ++ret;
    }
    return ret;
}

bool Gomoku::hasGameEnded(const sf::Vector2i& placedStone) const {
    if (_p1Captures >= 5 || _p2Captures >= 5) {
        return true;
    }
    const Tile lastMoved = _player == Player::PLAYERONE ? Tile::P1 : Tile::P2;

    std::vector<std::pair<std::function<void(sf::Vector2i&)>, std::function<void(sf::Vector2i&)>>> vec;
    vec.emplace_back([](sf::Vector2i& v) { --v.x; }, [](sf::Vector2i& v) { ++v.x; });
    vec.emplace_back([](sf::Vector2i& v) { --v.y; }, [](sf::Vector2i& v) { ++v.y; });
    vec.emplace_back([](sf::Vector2i& v) { --v.x; --v.y; }, [](sf::Vector2i& v) { ++v.x; ++v.y; });
    vec.emplace_back([](sf::Vector2i& v) { --v.x; ++v.y; }, [](sf::Vector2i& v) { ++v.x; --v.y; });

    for (const auto& [f1, f2]: vec) {
        if (totalInDirection(_board, f1, placedStone, lastMoved) +
            totalInDirection(_board, f2, placedStone, lastMoved) >= 4) {
            WARN("game has ended, player %d has won", static_cast<int>(_player) + 1);
            return true;
        }
    }

    return false;
}

Coordinate Gomoku::aiMove()
{
	LOG("Player which does the move %i", _player);
	auto result = _ai->AiMove(_board, _player);
	LOG("AI MOVE RESPONSE STRING = %s", result.errorString.c_str());
	LOG("The move is [%i][%i]", result.move.bestCoords.y, result.move.bestCoords.x);
	return result.move.bestCoords;
}
