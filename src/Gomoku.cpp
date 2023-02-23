//
// Created by Jonas Bennink Bolt on 2/3/23.
//

#include "Gomoku.hpp"
#include <SFML/Graphics.hpp>
#include <sstream>

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
                    if (event.key.code == sf::Keyboard::Key::Escape) {
                        _graphics->closeWindow();
                    }
                    break;
                }
                case sf::Event::MouseButtonPressed: {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        auto moveLocation = _graphics->nearestIntersection(event.mouseButton.x, event.mouseButton.y);
                        doMove(moveLocation);
                        // only redraw the board in this case because we don't change the board for other events
                        _graphics->update(_board);
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
    // TODO: validate if stone can be placed
    validateMove();

    std::stringstream ss;
    // probably this check will become part of the validator
    if (_board[moveLocation.y][moveLocation.x] == Tile::EMPTY) {
        // change _board to reflect new board state
        static int x = 1;
        if (++x % 2 == 0) {
            _board[moveLocation.y][moveLocation.x] = Tile::P1;
        } else {
            _board[moveLocation.y][moveLocation.x] = Tile::P2;
        }
        ss << "click at pos (" << moveLocation.x << "," << moveLocation.y << ")";
    } else {
        ss << "pos (" << moveLocation.x << ", " << moveLocation.y << ") is not valid, already has a stone";
    }
    // set header to whatever we want it to be
    _graphics->setHeader(ss.str());
}

void Gomoku::validateMove() {
//    _validator->validate();
}
