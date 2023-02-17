//
// Created by Jonas Bennink Bolt on 2/3/23.
//

#include "Graphics.hpp"
#include "logger.hpp"
#include "Gomoku.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <list>

using namespace sf;

Vector2<int> Graphics::nearestIntersection(int x, int y) const {
    auto lowerX = std::lower_bound(_xCoordinates.begin(), _xCoordinates.end(), x);
    // if end or not first and closer to left than to right
    if (lowerX == _xCoordinates.end() ||
        (lowerX != _xCoordinates.begin() && std::abs(x - *(lowerX - 1)) <= std::abs(x - *lowerX))) {
        --lowerX;
    }
    auto lowerY = std::lower_bound(_yCoordinates.begin(), _yCoordinates.end(), y);
    // same
    if (lowerY == _yCoordinates.end() ||
        (lowerY != _yCoordinates.begin() && std::abs(y - *(lowerY - 1)) <= std::abs(y - *lowerY))) {
        --lowerY;
    }
    return {*lowerX, *lowerY};
}

// leave this here to check how to make text later :)
//Text Graphics::tempTitle(const std::unique_ptr<RenderWindow>& window) {
//    Text topTitle;
//    topTitle.setFont(_font);
//    topTitle.setString("extra information goes at the top here");
//    topTitle.setFillColor(Color::Black);
//    topTitle.setStyle(Text::Bold);
//    // next steps are to center the text from left to right and in the top 10%
//    auto center = topTitle.getGlobalBounds().getSize() / 2.f;
//    auto localBounds = center + topTitle.getLocalBounds().getPosition();
//    Vector2f rounded = {std::round(localBounds.x), std::round(localBounds.y)};
//    topTitle.setOrigin(rounded);
//    topTitle.setPosition(Vector2f{static_cast<float>(window->getSize().x) / 2.f, static_cast<float>(window->getSize().y) / 20.f});
//    return topTitle;
//}

void Graphics::createLines() {
    const auto spacesBetweenLines = BOARD_SIZE + 1;
    _pixelsPerSpace = WINDOW_WIDTH / spacesBetweenLines;
    auto rem = WINDOW_WIDTH % spacesBetweenLines;
    const auto topPixelOffset = WINDOW_WIDTH * 0.1f;
    for (auto i = _pixelsPerSpace; i < WINDOW_WIDTH; i += _pixelsPerSpace) {
        if (rem-- > 0) {
            // spread extra pixels remainder over the first squares, 1 each
            ++i;
        }
        _xCoordinates.push_back(i);
        _yCoordinates.push_back(static_cast<int>(topPixelOffset) + i + 1);

        RectangleShape horizontalLine({WINDOW_WIDTH, 3});
        horizontalLine.setFillColor(Color::Black);
        horizontalLine.setPosition(0, topPixelOffset + static_cast<float>(i));
        _lines.push_back(horizontalLine);

        RectangleShape verticalLine({3, WINDOW_WIDTH});
        verticalLine.setFillColor(Color::Black);
        verticalLine.setPosition(static_cast<float>(i), topPixelOffset);
        _lines.push_back(verticalLine);
    }
}

Graphics::Graphics() : _pixelsPerSpace(0) {
    // TODO: check for WINDOW_WIDTH vs actual screen size and scale down if needed
    _window = std::make_unique<RenderWindow>(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Gomoku:)", Style::Default);
    _window->setVerticalSyncEnabled(true);
    _window->clear(Color::White);
    // path might change based on what directory
    if (not _font.loadFromFile("../resources/Arial.ttf")) {
        LOG("font not loaded from file");
    }

    createLines();
}

void Graphics::placeStone(int x, int y) {
    auto loc = nearestIntersection(x, y);
    float radius = static_cast<float>(_pixelsPerSpace) / 2 * CIRCLE_SCALE;
    CircleShape newStone(radius);
    // TODO: now it just alternates color based on this x
    static int clr = 0;
    newStone.setFillColor(++clr % 2 == 0 ? Color::Red : Color::Blue);
    newStone.setPosition(static_cast<float>(loc.x) - radius, static_cast<float>(loc.y) - radius);
    _stones.push_back(newStone);
}

bool Graphics::isWindowOpen() const {
    return _window->isOpen();
}

void Graphics::closeWindow() {
    _window->close();
}

std::optional<sf::Event> Graphics::getEvent() {
    std::optional<Event> ev{};
    if (not _window->pollEvent(ev.emplace())) {
        return std::nullopt;
    }
    return ev;
}

void Graphics::update() {
    _window->clear(Color::White);
    for (const auto& shape: _lines) {
        _window->draw(shape);
    }
    for (const auto& circle: _stones) {
        _window->draw(circle);
    }
    _window->display();
}
