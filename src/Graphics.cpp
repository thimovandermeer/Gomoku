//
// Created by Jonas Bennink Bolt on 2/3/23.
//

#include "Graphics.hpp"
#include "logger.hpp"
#include "Gomoku.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <fmt/core.h>

using namespace sf;

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

void createButton(Button& button, const std::string& content, const Vector2f& position, const Vector2f& size,
                  const Font& font) {
    button.setSize(size);
    button.setFillColor(Color::Black);
    button.setPosition(position);

    auto& txt = button.mutableText();
    txt.setFont(font);
    txt.setCharacterSize(static_cast<unsigned int>(size.x / 6.5f));
    txt.setFillColor(Color::White);
    button.setText(content);

    const FloatRect bounds(txt.getLocalBounds());
    const Vector2f box(button.getSize());
    txt.setOrigin((bounds.width - box.x) / 2 + bounds.left, (bounds.height - box.y) / 2 + bounds.top);
    txt.setPosition(button.getPosition());
}

Graphics::Graphics() : _rulesActive(false), _pixelsPerSpace(0) {
    // checking vs screen size does not seem to work properly since it checks physical pixels, nothing scaled
    _window = std::make_unique<RenderWindow>(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Gomoku :)",
                                             Style::Titlebar | Style::Close);
    _window->setVerticalSyncEnabled(true);
    _window->clear(Color::White);

    std::string resourcePath(PROJECT_ROOT_DIR);
    resourcePath += "/resources/";
    auto icon = Image{};
    if (not icon.loadFromFile(resourcePath + "icon.png")) {
        ERROR("icon not loaded from file");
        _window->close();
        return;
    }
    _window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    if (not _font.loadFromFile(resourcePath + "Arial.ttf")) {
        ERROR("font not loaded from file");
        _window->close();
        return;
    }
    _header.setFont(_font);
    _header.setFillColor(Color::Black);
    _header.setCharacterSize(WINDOW_WIDTH * (0.1 / MAX_HEADER_LINES));

    _captures.setFont(_font);
    _captures.setFillColor(Color::Black);
    _captures.setCharacterSize(WINDOW_WIDTH * (0.08 / MAX_HEADER_LINES));
    createLines();
    Vector2f cornerButtonSize{WINDOW_WIDTH * 0.125, WINDOW_HEIGHT * 0.03};
    createButton(_rulesButton, "Rules", {WINDOW_WIDTH - (WINDOW_WIDTH * 0.175), WINDOW_HEIGHT * 0.014},
                 cornerButtonSize, _font);
    createButton(_suggestMoveButton, "Hint", {WINDOW_WIDTH - (WINDOW_WIDTH * 0.175), WINDOW_HEIGHT * 0.046},
                 cornerButtonSize, _font);
    Vector2f gameModeSelectButtonSize{WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.06};
    createButton(_singleplayerButton, "1 player game", {static_cast<float>(WINDOW_WIDTH) / 2 - WINDOW_WIDTH * 0.15,
                                                        WINDOW_HEIGHT / 2 - WINDOW_HEIGHT * 0.03 -
                                                        WINDOW_HEIGHT * 0.12}, gameModeSelectButtonSize, _font);
    createButton(_multiplayerButton, "2 player game", {static_cast<float>(WINDOW_WIDTH) / 2 - WINDOW_WIDTH * 0.15,
                                                       WINDOW_HEIGHT / 2 - WINDOW_HEIGHT * 0.03 + WINDOW_HEIGHT * 0.12},
                 gameModeSelectButtonSize, _font);
    _stoneSize = static_cast<float>(_pixelsPerSpace) * CIRCLE_SCALE;

    if (not _boardTexture.loadFromFile(resourcePath + "board.jpg")) {
        ERROR("board image not loaded from file");
        _window->close();
        return;
    }
    _boardImage.setTexture(_boardTexture);

    Vector2u textureSize = _boardTexture.getSize();
    Vector2u windowSize = _window->getSize();
    Vector2f boardScale = {static_cast<float>(windowSize.x) / static_cast<float>(textureSize.x),
                           static_cast<float>(windowSize.y) / static_cast<float>(textureSize.y)};
    _boardImage.setScale(boardScale);

    if (not _blackStone.loadFromFile(resourcePath + "blackStone.png")) {
        ERROR("black stone not loaded from file");
        _window->close();
        return;
    }
    _blackStone.setSmooth(true);
    if (not _whiteStone.loadFromFile(resourcePath + "whiteStone.png")) {
        ERROR("white stone not loaded from file");
        _window->close();
        return;
    }
    _whiteStone.setSmooth(true);
}

bool Graphics::isWindowOpen() const {
    return _window->isOpen();
}

void Graphics::closeWindow() {
    _window->close();
}

std::optional<sf::Event> Graphics::getEvent() {
    Event ev{};
    if (not _window->pollEvent(ev)) {
        return std::nullopt;
    }
    return ev;
}

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

void Graphics::setHeader(const std::string& text) {
    if (std::count(text.begin(), text.end(), '\n') > MAX_HEADER_LINES - 1) {
        WARN("Attempting to put too many lines in header, leaving header unchanged.");
        return;
    }
    _header.setString(text);
    auto center = _header.getGlobalBounds().getSize() / 2.f;
    auto localBounds = center + _header.getLocalBounds().getPosition();
    Vector2f rounded = {std::round(localBounds.x), std::round(localBounds.y)};
    _header.setOrigin(rounded);
    _header.setPosition(
            {static_cast<float>(_window->getSize().x) / 2.f, static_cast<float>(_window->getSize().y) / 20.f});
}

std::optional<ButtonId> Graphics::ButtonClick(const Vector2i& loc, bool firstScreen) const {
    if (_rulesButton.contains(loc)) {
        return ButtonId::RULES;
    }
    if (_suggestMoveButton.contains(loc)) {
        return ButtonId::SUGGEST_MOVE;
    }
    if (not firstScreen) {
        return std::nullopt;
    }
    if (_singleplayerButton.contains(loc)) {
        return ButtonId::SINGLEPLAYER_GAME;
    }
    if (_multiplayerButton.contains(loc)) {
        return ButtonId::MULTIPLAYER_GAME;
    }
    return std::nullopt;
}

void Graphics::setRulesActive(bool b) {
    _rulesButton.setText(b ? " Back" : "Rules");
    _rulesActive = b;
}

bool Graphics::getRulesActive() const {
    return _rulesActive;
}

void Graphics::addStone(int x, int y, Tile player, std::vector<Sprite>& stones, std::vector<Text>& stoneText) {
    Vector2<int> loc = {_xCoordinates[x], _yCoordinates[y]};

    const Texture& texture = player == Tile::P1 ? _blackStone : _whiteStone;
    Sprite sprt(texture);
    auto textureSize = texture.getSize();
    Vector2f sizeF{static_cast<float>(textureSize.x), static_cast<float>(textureSize.y)};
    sprt.setScale(_stoneSize / sizeF.x, _stoneSize / sizeF.y);
    sprt.setPosition(static_cast<float>(loc.x) - _stoneSize / 2, static_cast<float>(loc.y) - _stoneSize / 2);
    stones.push_back(sprt);

#ifdef DEBUG_STONE_COORDINATES
    Text txt{};
    txt.setFont(_font);
    txt.setFillColor(player == Tile::P1 ? Color::White : Color::Black);
    txt.setCharacterSize(static_cast<unsigned int>(_stoneSize * 0.3));
    txt.setStyle(Text::Bold);
    txt.setString(fmt::format("{},{}", x, y));
    auto center = txt.getGlobalBounds().getSize() / 2.f;
    auto localbounds = center + txt.getLocalBounds().getPosition();
    Vector2f rounded = {std::round(localbounds.x), std::round(localbounds.y)};
    txt.setOrigin(rounded);
    txt.setPosition({static_cast<float>(loc.x), static_cast<float>(loc.y)});
    stoneText.push_back(txt);
#else
    (void)stoneText;
#endif
}

void Graphics::drawRules() {
    constexpr std::string_view DA_RULES =
            "\n\t(press Esc to return to the game)\n\n"
            "\tThe goal of the game is to get five in a row by placing stones alternating\n"
            "\tbetween both players.\n\n"
            "\tCapture: you can remove a pair of your opponent's stones from the board\n"
            "\tby flanking them with your own stones. You also win if you capture ten of\t\n"
            "\tyour opponent's stones, so a total of five captures.\n\n"
            "\tYou only win with five in a row if these five cannot be broken by a capture.\n\n"
            "\tIt is not allowed to play a move that creates two free-three alignments,\n"
            "\texcept by capturing a pair from your opponent.";
    Text rules;
    rules.setFont(_font);
    rules.setFillColor(Color::Black);
    rules.setCharacterSize(WINDOW_WIDTH / 40);
    rules.setString(std::string{DA_RULES});
    rules.setPosition(WINDOW_WIDTH * 0.05, WINDOW_HEIGHT * 0.05);

    _window->draw(_rulesButton);
    _window->draw(_rulesButton.text());
    _window->draw(rules);
    _window->display();
}

void Graphics::update(const std::vector<std::vector<Tile>>& board, int p1Captures, int p2Captures) {
    _window->clear(Color::White);
    _window->draw(_boardImage);
    if (_rulesActive) {
        drawRules();
        return;
    }
    // create circles to place on the board
    std::vector<Text> stoneText;
    std::vector<Sprite> stones;
    for (int y = 0; y < BOARD_SIZE; ++y) {
        for (int x = 0; x < BOARD_SIZE; ++x) {
            if (board[y][x] != Tile::EMPTY) {
                addStone(x, y, board[y][x], stones, stoneText);
            }
        }
    }

    _captures.setString(fmt::format("P1 caps: {}\nP2 caps: {}", p1Captures, p2Captures));

    _window->draw(_header);
    _window->draw(_rulesButton);
    _window->draw(_rulesButton.text());
    _window->draw(_suggestMoveButton);
    _window->draw(_suggestMoveButton.text());
    _window->draw(_captures);
    for (const auto& shape: _lines) {
        _window->draw(shape);
    }
    for (const auto& stone: stones) {
        _window->draw(stone);
    }
#ifdef DEBUG_STONE_COORDINATES
    for (const auto& txt: stoneText) {
        _window->draw(txt);
    }
#endif
    _window->display();
}

void Graphics::drawGameSelect() {
    _window->clear(Color::White);
    _window->draw(_boardImage);
    _window->draw(_singleplayerButton);
    _window->draw(_singleplayerButton.text());
    _window->draw(_multiplayerButton);
    _window->draw(_multiplayerButton.text());
    _window->display();
}
