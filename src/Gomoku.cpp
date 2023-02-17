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
                    // TODO: validate if stone can be placed
                    std::stringstream ss;
                    ss << "click at (" << event.mouseButton.x << "," << event.mouseButton.y << ")";
                    _graphics->setHeader(ss.str());
                    _graphics->placeStone(event.mouseButton.x, event.mouseButton.y);
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

void Gomoku::doMove() {

}

void Gomoku::validateMove() {
//    _validator->validate();
}
