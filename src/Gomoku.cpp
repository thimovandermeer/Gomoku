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

    auto buttonClick = _graphics->ButtonClick({event.mouseButton.x, event.mouseButton.y},
                                              _gameType == GameType::INVALID);
    if (_gameType == GameType::INVALID) {
        if (buttonClick.has_value() && buttonClick.value() == ButtonId::SINGLEPLAYER_GAME) {
            _gameType = GameType::SINGLEPLAYER;
            _graphics->update(_board, _p1Captures, _p2Captures);
        }
        if (buttonClick.has_value() && buttonClick.value() == ButtonId::MULTIPLAYER_GAME) {
            _gameType = GameType::MULTIPLAYER;
            _graphics->update(_board, _p1Captures, _p2Captures);
        }
        return;
    }

    if (buttonClick.has_value() && buttonClick.value() == ButtonId::RULES) {
        // toggle rules
        _graphics->setRulesActive(not _graphics->getRulesActive());
        _graphics->update(_board, _p1Captures, _p2Captures);
        return;
    } else if (buttonClick.has_value() && buttonClick.value() == ButtonId::SUGGEST_MOVE) {
        WARN("suggest move");
        // TODO: get AI suggestion
        Coordinate move{-1, -1};
        _graphics->setHeader(fmt::format("{}, {} is the suggested move", move.x, move.y));
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
        // player has swapped already in doMove(), so we report the opposite of the "current" player
        int winningPlayer = _player == Player::PLAYERONE ? 2 : 1;
        _graphics->setHeader(fmt::format("Player {} has won!", winningPlayer));
    }
    // only redraw the board in this case because we don't change the board for other events
    _graphics->update(_board, _p1Captures, _p2Captures);
}

void Gomoku::gameLoop() {
    _graphics->drawGameSelect();
    while (true) {
        if (not _graphics->isWindowOpen()) {
            // potential cleanup, but essentially the window is closed, so we exit
            return;
        }
        // TODO: remove this tmp, only to print log msg 1 time per AI move
        static bool tmp = true;
        if (not _gameEnd && _gameType == GameType::SINGLEPLAYER && _player == Player::PLAYERTWO) {
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
            if (newMove.y != -1 && newMove.x != -1) {
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
        _capturedCoords.emplace_back(first, second);
        return true;
    }
    return false;
}

void Gomoku::findCapture(const sf::Vector2i& moveLocation) {
    for (const auto& [dir1, dir2]: _moveDirections) {
        findCaptureInDirection(dir1, moveLocation);
        findCaptureInDirection(dir2, moveLocation);
    }
}

void Gomoku::capture(const sf::Vector2i& moveLocation) {
    _capturedCoords.clear();
    findCapture(moveLocation);
    if (not _capturedCoords.empty()) {
        for (const auto& [first, second]: _capturedCoords) {
            _board[first.y][first.x] = Tile::EMPTY;
            _board[second.y][second.x] = Tile::EMPTY;

            if (_player == Player::PLAYERONE) {
                ++_p1Captures;
            } else {
                ++_p2Captures;
            }
        }
    }
}

void Gomoku::undoCapture() {
    Tile toSetBack = _player == Player::PLAYERONE ? Tile::P2 : Tile::P1;
    for (const auto& [first, second]: _capturedCoords) {
        _board[first.y][first.x] = toSetBack;
        _board[second.y][second.x] = toSetBack;

        if (_player == Player::PLAYERONE) {
            --_p1Captures;
        } else {
            --_p2Captures;
        }
    }
    _capturedCoords.clear();
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
        if (not _capturedCoords.empty()) {
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
                            const sf::Vector2i& start, const Tile& val, std::vector<sf::Vector2i>& row) {
    sf::Vector2i checkPos = start;
    int ret = 0;
    for (int i = 0; i < 4; ++i) {
        move(checkPos);
        if (not isInBounds(checkPos) || not isCorrectTile(board, checkPos, val)) {
            return ret;
        }
        row.push_back(checkPos);
        ++ret;
    }
    return ret;
}

static bool capturableSequence(const std::vector<Tile>& seq) {
    Tile middlePlayer = seq[2];
    Tile capturingPlayer = middlePlayer == Tile::P1 ? Tile::P2 : Tile::P1;

    // * doesn't matter
    // . empty
    // X middle player
    // O capturing player
    // * . X X O
    if (seq[1] == Tile::EMPTY && seq[3] == middlePlayer && seq[4] == capturingPlayer) {
        return true;
    }
    // O X X . *
    if (seq[0] == capturingPlayer && seq[1] == middlePlayer && seq[3] == Tile::EMPTY) {
        return true;
    }
    // . X X O *
    if (seq[0] == Tile::EMPTY && seq[1] == middlePlayer && seq[3] == capturingPlayer) {
        return true;
    }
    // * O X X .
    if (seq[1] == capturingPlayer && seq[3] == middlePlayer && seq[4] == Tile::EMPTY) {
        return true;
    }

    return false;
}

bool Gomoku::canBeCapturedInDirection(
        const std::pair<std::function<void(sf::Vector2i&)>, std::function<void(sf::Vector2i&)>>& dir,
        const sf::Vector2i& location) const {
    auto current{location};
    dir.first(current);
    dir.first(current);
    std::vector<Tile> sequence{};
    for (int i = 0; i <= 5; ++i) {
        if (isInBounds(current)) {
            sequence.push_back(_board[current.y][current.x]);
        } else {
            sequence.push_back(Tile::OOB);
        }
        dir.second(current);
    }
    return capturableSequence(sequence);
}

bool Gomoku::canBeCaptured(const sf::Vector2i& location) const {
    if (_board[location.y][location.x] == Tile::EMPTY) {
        return false;
    }
    for (const auto& direction: _moveDirections) {
        if (canBeCapturedInDirection(direction, location)) {
            return true;
        }
    }
    return false;
}

bool Gomoku::hasGameEnded(const sf::Vector2i& placedStone) const {
    if (_p1Captures >= 5 || _p2Captures >= 5) {
        return true;
    }
    const Tile lastMoved = _player == Player::PLAYERONE ? Tile::P1 : Tile::P2;

    for (const auto& [f1, f2]: _moveDirections) {
        std::vector<sf::Vector2i> winningRow{placedStone};
        if (totalInDirection(_board, f1, placedStone, lastMoved, winningRow) +
            totalInDirection(_board, f2, placedStone, lastMoved, winningRow) >= 4) {
            for (const auto& pos: winningRow) {
                if (canBeCaptured(pos)) {
                    WARN("win can be broken by capture");
                    return false;
                }
            }
            WARN("game has ended, player %d has won", static_cast<int>(_player) + 1);
            return true;
        }
    }

    return false;
}

Coordinate Gomoku::aiMove() {
    auto result = _ai->AiMove(_board, _player);
    return result.move.bestCoords;
}
