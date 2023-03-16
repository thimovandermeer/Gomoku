//
// Created by Jonas Bennink Bolt on 2/3/23.
//

#include "Gomoku.hpp"
#include <SFML/Graphics.hpp>
#include <sstream>
#include "types.hpp"

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

void Gomoku::doMove(const sf::Vector2<int>& moveLocation) {
    // TODO: validate if stone can be placed
    Coordinates coords{moveLocation.y, moveLocation.x};
    std::stringstream ss;
    LOG("coords y: %i, x: %i");

    if (_state.state == State::ACCEPTED) {
        _player = _player == Player::PLAYERONE ? Player::PLAYERTWO : Player::PLAYERONE;
    }
    validateMove(coords, ss);


    // probably this check will become part of the validator
    if (_state.state == State::ACCEPTED) {
        // change _board to reflect new board state
        if (_player == Player::PLAYERONE) {
            _board[moveLocation.y][moveLocation.x] = Tile::P1;
        } else {
            _board[moveLocation.y][moveLocation.x] = Tile::P2;
        }
    }
    ss << "\n\t\tat (" << moveLocation.x << ", " << moveLocation.y << ")";
    // set header to whatever we want it to be
    _graphics->setHeader(ss.str());

}

void Gomoku::validateMove(Coordinates coords, std::stringstream &ss) {
    LOG("Coords zijn y:%i x: %i", coords.y, coords.x);
    if(_player == Player::PLAYERONE) {
        _state = _validator_container->p1_validate(_board, coords, _player);
    } else {
        _state = _validator_container->p2_validate(_board, coords, _player);
    }
    LOG("Result = %s", _state.error_reason.c_str());
    LOG("Result = %i", _state.state);
    ss << _state.error_reason.c_str();
}
