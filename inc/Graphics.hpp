//
// Created by Jonas Bennink Bolt on 2/3/23.
//

#ifndef GOMOKU_GRAPHICS_HPP
#define GOMOKU_GRAPHICS_HPP

#include <memory>
#include <SFML/Graphics.hpp>
#include "types.hpp"

#ifndef PROJECT_ROOT_DIR
#define PROJECT_ROOT_DIR "."
#endif
// game becomes near unplayable if BOARD_SIZE * 10 >= WINDOW_WIDTH
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT (WINDOW_WIDTH * 1.1f)
#define CIRCLE_SCALE 0.75f
#define MAX_HEADER_LINES 2

enum class Tile;

class IGraphics {
public:
    virtual ~IGraphics() = default;
    virtual bool isWindowOpen() const = 0;
    virtual void closeWindow() = 0;
    virtual std::optional<sf::Event> getEvent() = 0;
    virtual void setHeader(const std::string& text) = 0;
    virtual std::optional<sf::Vector2<int>> nearestIntersection(int x, int y) const = 0;
    virtual std::optional<ButtonId> ButtonClick(const sf::Vector2i& loc, bool isGameSelect) const = 0;
    virtual void setRulesActive(bool b) = 0;
    virtual bool getRulesActive() const = 0;
    virtual void update(const std::vector<std::vector<Tile>>& board, const std::pair<int, int>& captures) = 0;
    virtual void drawGameSelect() = 0;
};

class Button : public sf::RectangleShape {
public:
    void setText(const std::string& txt) { _text.setString(txt); }
    const sf::Text& text() const { return _text; }
    sf::Text& mutableText() { return _text; }
    bool contains(const sf::Vector2i& loc) const {
        sf::IntRect b(getGlobalBounds());
        return b.contains(loc);
    }
private:
    sf::Text _text;
};

class Graphics : public IGraphics {
public:
    Graphics();
    Graphics(const Graphics&) = delete;
    Graphics& operator=(const Graphics&) = delete;
    ~Graphics() override = default;

    bool isWindowOpen() const override;
    void closeWindow() override;

    std::optional<sf::Event> getEvent() override;
    std::optional<sf::Vector2<int>> nearestIntersection(int x, int y) const override;
    void setHeader(const std::string& text) override;
    std::optional<ButtonId> ButtonClick(const sf::Vector2i& loc, bool isGameSelect) const override;
    void setRulesActive(bool b) override;
    bool getRulesActive() const override;

    void update(const std::vector<std::vector<Tile>>& board, const std::pair<int, int>& captures) override;
    void drawGameSelect() override;

private:
    sf::Text _header;
    bool _rulesActive;
    Button _rulesButton;
    sf::Text _captures;

// these are (likely) set only once
    Button _suggestMoveButton;
    Button _singleplayerButton;
    Button _multiplayerButton;
    std::unique_ptr<sf::RenderWindow> _window;
    sf::Font _font;
    std::vector<int> _xCoordinates;
    std::vector<int> _yCoordinates;
    std::vector<sf::RectangleShape> _lines;
    int _pixelsPerSpace;
    float _stoneSize;
    sf::Texture _blackStone;
    sf::Texture _whiteStone;
    sf::Texture _boardTexture;
    sf::Sprite _boardImage;

    void createLines();
    void addStone(int x, int y, Tile player, std::vector<sf::Sprite>& stones, std::vector<sf::Text>& stoneText);
    void drawRules();
};

#endif //GOMOKU_GRAPHICS_HPP
