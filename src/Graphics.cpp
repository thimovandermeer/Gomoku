//
// Created by Jonas Bennink Bolt on 2/3/23.
//

#include "Graphics.hpp"
#include "logger.hpp"
#include "Gomoku.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>

using namespace sf;

std::optional<sf::Vector2<int>> Graphics::nearestIntersection(int x, int y) const {
    if (static_cast<float>(y) < WINDOW_WIDTH * 0.1f) {
        return std::nullopt;
    }
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
    return {{static_cast<int>(lowerX - _xCoordinates.begin()), static_cast<int>(lowerY - _yCoordinates.begin())}};
}

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
    // checking vs screen size does not seem to work properly since it checks physical pixels, nothing scaled
    _window = std::make_unique<RenderWindow>(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Gomoku :)",
                                             Style::Titlebar | Style::Close);
    _window->setVerticalSyncEnabled(true);
    _window->clear(Color::White);

    std::string pathToFont(PROJECT_ROOT_DIR);
    if (not _font.loadFromFile(pathToFont + "/resources/Arial.ttf")) {
        LOG("font not loaded from file");
    }
    _header.setFont(_font);
    _header.setFillColor(Color::Black);
    _header.setCharacterSize(WINDOW_WIDTH * (0.1 / MAX_HEADER_LINES));
    createLines();
    _stoneRadius = static_cast<float>(_pixelsPerSpace) / 2 * CIRCLE_SCALE;
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

void Graphics::setHeader(const std::string& text) {
    if (std::count(text.begin(), text.end(), '\n') > MAX_HEADER_LINES - 1) {
        LOG("Attempting to put too many lines in header, leaving header unchanged.");
        return;
    }
    _header.setString(text);
    auto center = _header.getGlobalBounds().getSize() / 2.f;
    auto localBounds = center + _header.getLocalBounds().getPosition();
    Vector2f rounded = {std::round(localBounds.x), std::round(localBounds.y)};
    _header.setOrigin(rounded);
    _header.setPosition(
            Vector2f{static_cast<float>(_window->getSize().x) / 2.f, static_cast<float>(_window->getSize().y) / 20.f});
}

CircleShape Graphics::newStone(int x, int y, Color clr) {
    Vector2<int> loc = {_xCoordinates[x], _yCoordinates[y]};
    CircleShape ret(_stoneRadius);
    ret.setFillColor(clr);
    ret.setPosition(static_cast<float>(loc.x) - _stoneRadius, static_cast<float>(loc.y) - _stoneRadius);
    return ret;
}

void Graphics::update(const std::vector<std::vector<Tile>>& board) {
    // create circles to place on the board
    std::vector<CircleShape> stones;
    for (int y = 0; y < BOARD_SIZE; ++y) {
        for (int x = 0; x < BOARD_SIZE; ++x) {
            if (board[y][x] == Tile::P1) {
                stones.push_back(newStone(x, y, Color::Blue));
            } else if (board[y][x] == Tile::P2) {
                stones.push_back(newStone(x, y, Color::Red));
            }
        }
    }
    _window->clear(Color::White);
    _window->draw(_header);
    for (const auto& shape: _lines) {
        _window->draw(shape);
    }
    for (const auto& stone: stones) {
        _window->draw(stone);
    }
    _window->display();
}
