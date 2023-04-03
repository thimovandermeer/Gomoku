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
    // draw board for the first time
    _graphics->update(_board, _p1Captures, _p2Captures);
    // hack;
    while (true) {
        if (not _graphics->isWindowOpen()) {
            // potential cleanup, but essentially the window is closed, so we exit
            return;
        }
        // TODO: remove this tmp, only to print log msg 1 time per AI move
        static bool tmp = true;
        if (_player == Player::PLAYERTWO) {
            // TODO: AI move here
            if (tmp) {
                WARN("AI should move now");
                tmp = false;
            }
            WARN("before ai call");
//             ai call
            Coordinate newMove = aiMove();
//             do move
            WARN("after ai call");
            if(newMove.y != -1 && newMove.x != -1) {
                sf::Vector2<int> move;
                move.y = newMove.y;
                move.x = newMove.x;
                WARN("We are going to do the move %i %i", move.y, move.x);
                doMove({newMove.x, newMove.y});
                // assuming AI always does a valid move, board can be udpated
                _graphics->update(_board, _p1Captures, _p2Captures);
            }
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
                    tmp = true;
                    break;
                }
                default:
                    break;
            }

            eventWrapper = _graphics->getEvent();
        }
    }
}

static bool isCorrectTile(const std::vector<std::vector<Tile>>& board, const sf::Vector2i& pos, const Tile& val) {
    return board[pos.y][pos.x] == val;
}

static bool isInBounds(const sf::Vector2i& pos) {
    return pos.x >= 0 && pos.x < BOARD_SIZE && pos.y >= 0 && pos.y < BOARD_SIZE;
}


bool Gomoku::findCaptureInDirection(const std::function<void(sf::Vector2i&)>& move, const sf::Vector2i& moveLocation) {
    sf::Vector2i loc = moveLocation;
    Tile own = _player == Player::PLAYERONE ? Tile::P1 : Tile::P2;
    Tile toCapture = own == Tile::P1 ? Tile::P2 : Tile::P1;
    move(loc);
    sf::Vector2i first(loc);
    move(loc);
    sf::Vector2i second(loc);
    move(loc);
    sf::Vector2i third(loc);
    if (not isInBounds(first) || not isInBounds(second) || not isInBounds(third)) {
        return false;
    }
    if (isCorrectTile(_board, first, toCapture) && isCorrectTile(_board, second, toCapture) &&
        isCorrectTile(_board, third, own)) {
        _capturedCoords = {first, second};
        return true;
    }
    return false;
}

bool Gomoku::findCapture(const sf::Vector2i& moveLocation) {
    for (const auto& [dir1, dir2]: _moveDirections) {
        if (findCaptureInDirection(dir1, moveLocation)) {
            return true;
        }
        if (findCaptureInDirection(dir2, moveLocation)) {
            return true;
        }
    }
    return false;
}

void Gomoku::capture(const sf::Vector2i& moveLocation) {
    // TODO: think about double capture
    _capturedCoords = {{-1, -1}, {-1, -1}};
    if (findCapture(moveLocation)) {
        _board[_capturedCoords.first.y][_capturedCoords.first.x] = Tile::EMPTY;
        _board[_capturedCoords.second.y][_capturedCoords.second.x] = Tile::EMPTY;
        if (_player == Player::PLAYERONE) {
            ++_p1Captures;
        } else {
            ++_p2Captures;
        }
    }
}

void Gomoku::undoCapture() {
    Tile toSetBack = _player == Player::PLAYERONE ? Tile::P2 : Tile::P1;
    _board[_capturedCoords.first.y][_capturedCoords.first.x] = toSetBack;
    _board[_capturedCoords.second.y][_capturedCoords.second.x] = toSetBack;
    if (_player == Player::PLAYERONE) {
        --_p1Captures;
    } else {
        --_p2Captures;
    }
    _capturedCoords = {{-1, -1}, {-1, -1}};
}

void Gomoku::doMove(const sf::Vector2<int>& moveLocation) {
    if (_board[moveLocation.y][moveLocation.x] != Tile::EMPTY) {
        _graphics->setHeader(fmt::format("location not empty\n\tat ({}, {})", moveLocation.x, moveLocation.y));
        return;
    }
    _board[moveLocation.y][moveLocation.x] = _player == Player::PLAYERONE ? Tile::P1 : Tile::P2;
    capture(moveLocation);

    // probably this check will become part of the validator
    if (validateMove()) {
        _gameEnd = hasGameEnded(moveLocation);
        _graphics->setHeader(fmt::format("placed stone\n\tat ({}, {})", moveLocation.x, moveLocation.y));

        _player = _player == Player::PLAYERONE ? Player::PLAYERTWO : Player::PLAYERONE;
    } else {
        // undo move that is not ok
        _board[moveLocation.y][moveLocation.x] = Tile::EMPTY;
        _graphics->setHeader(fmt::format("move creates 2 open threes\n\tat ({}, {})", moveLocation.x, moveLocation.y));
        // undo capture if necessary
        if (_capturedCoords.first.x != -1) {
            undoCapture();
        }
    }
}

bool Gomoku::validateMove() {
//	_state = _validator->validate(_board, coords, _player);
    NewValidator validator(_board, _player);
    return validator.validate();
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

    for (const auto& [f1, f2]: _moveDirections) {
        if (totalInDirection(_board, f1, placedStone, lastMoved) +
            totalInDirection(_board, f2, placedStone, lastMoved) >= 4) {
            WARN("game has ended, player %d has won", static_cast<int>(_player) + 1);
            return true;
        }
    }

    // TODO: check if it can be broken by capture

    return false;
}

Coordinate Gomoku::aiMove() {
    auto result = _ai->AiMove(_board, _player);
    return result.move.bestCoords;
}
