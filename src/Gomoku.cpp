//
// Created by Jonas Bennink Bolt on 2/3/23.
//

#include "Gomoku.hpp"
#include <SFML/Graphics.hpp>
#include <sstream>

void Gomoku::handleKeyPressed(const sf::Event& event) {
    if (event.key.code == sf::Keyboard::Key::Escape) {
        if (_graphics->getRulesActive()) {
            _graphics->setRulesActive(false);
            _graphics->update(_board);
        } else {
            _graphics->closeWindow();
        }
    }
}

void Gomoku::handleMouseButtonPressed(const sf::Event& event) {
    if (event.mouseButton.button == sf::Mouse::Left) {
        if (_graphics->isRulesClick({event.mouseButton.x, event.mouseButton.y})) {
            // toggle rules
            _graphics->setRulesActive(not _graphics->getRulesActive());
            _graphics->update(_board);
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
        // only redraw the board in this case because we don't change the board for other events
        _graphics->update(_board);
    }
}

void Gomoku::gameLoop() {
    // draw board for the first time
    _graphics->update(_board);
    while (true) {
        if (not _graphics->isWindowOpen()) {
            // potential cleanup, but essentially the window is closed, so we exit
            return;
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
                    handleMouseButtonPressed(event);
                    break;
                }
                default:
                    break;
            }

            eventWrapper = _graphics->getEvent();
        }
    }
}

void Gomoku::whichPlayer() {
    static int x = 1;
    if (++x % 2 == 0) {
        _player = Player::PLAYERONE;
    } else {
        _player = Player::PLAYERTWO;
    }
}

void Gomoku::doMove(const sf::Vector2<int>& moveLocation) {
    // TODO: validate if stone can be placed
    whichPlayer();
    Coordinates coords{moveLocation.y, moveLocation.x};
    LOG("coords y: %i, x: %i");
    validateMove(coords);



    std::stringstream ss;
    // probably this check will become part of the validator
    if (_board[moveLocation.y][moveLocation.x] == Tile::EMPTY) {
        // change _board to reflect new board state
        if (_player == Player::PLAYERONE) {
            _board[moveLocation.y][moveLocation.x] = Tile::P1;
        } else {
            _board[moveLocation.y][moveLocation.x] = Tile::P2;
        }
        ss << "click at pos (" << moveLocation.x << "," << moveLocation.y << ")";
    } else {
        ss << "pos (" << moveLocation.x << ", " << moveLocation.y << ") is not allowed";
    }
    // set header to whatever we want it to be
    _graphics->setHeader(ss.str());

}

void Gomoku::validateMove(Coordinates coords) {
    errorState result;
    if(_player == Player::PLAYERONE) {
        result = _validator_P1->validate(_board, coords, _player);
    } else {
        LOG("VOLGENS MIJ CRASH DIT");
        result = _validator_P2->validate(_board, coords, _player);
        LOG("JAAA");
    }
    LOG("Result = %s", result.error_reason.c_str());
    LOG("Result = %i", result.state);
}
