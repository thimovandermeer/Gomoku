//
// Created by Jonas Bennink Bolt on 2/3/23.
//

#include "Gomoku.hpp"
#include <SFML/Graphics.hpp>
#include <sstream>

void Gomoku::gameLoop() {
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
                    doMove(event.mouseButton);
                    break;
                }
                default:
                    break;
            }

            _graphics->update();
            eventWrapper = _graphics->getEvent();
        }
    }
}

void Gomoku::doMove(const sf::Event::MouseButtonEvent& event) {
    // TODO: validate if stone can be placed
    validateMove();

    // set header to whatever we want it to be
    std::stringstream ss;
    ss << "click at (" << event.x << "," << event.y << ")";
    _graphics->setHeader(ss.str());

    // pass stone to be placed
    // probably pass (x,y) on the board instead of pixel clicks, and pass which player stone
    _graphics->placeStone(event.x, event.y);

    // pass (potential) stone to be removed
    // _graphics->removeStone(x, y);
}

void Gomoku::validateMove() {
//    _validator->validate();
}
