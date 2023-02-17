//
// Created by Jonas Bennink Bolt on 2/3/23.
//

#ifndef GOMOKU_GRAPHICS_HPP
#define GOMOKU_GRAPHICS_HPP

#include <memory>
#include <SFML/Graphics.hpp>

#ifndef PROJECT_ROOT_DIR
#define PROJECT_ROOT_DIR "."
#endif
// game becomes near unplayable if BOARD_SIZE * 10 >= WINDOW_WIDTH
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT (WINDOW_WIDTH * 1.1f)
#define CIRCLE_SCALE 0.75f
#define MAX_HEADER_LINES 2

class IGraphics {
public:
    virtual ~IGraphics() = default;
    virtual bool isWindowOpen() const = 0;
    virtual void closeWindow() = 0;
    virtual std::optional<sf::Event> getEvent() = 0;
    virtual void placeStone(int x, int y) = 0;
    virtual void setHeader(const std::string& text) = 0;
    virtual void update() = 0;
};

class EmptyGraphics : public IGraphics {
public:
    bool isWindowOpen() const override { return false; }
    void closeWindow() override {}
    std::optional<sf::Event> getEvent() override { return std::nullopt; }
    void placeStone(int x, int y) override { (void)(x + y); }
    void setHeader(const std::string& text) override { (void)text; };
    void update() override {}
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
    void placeStone(int x, int y) override;
    void setHeader(const std::string& text) override;
    void update() override;

private:
    std::vector<sf::CircleShape> _stones;
    sf::Text _header;

// these are (likely) set only once
    std::unique_ptr<sf::RenderWindow> _window;
    sf::Font _font;
    std::vector<int> _xCoordinates;
    std::vector<int> _yCoordinates;
    std::vector<sf::RectangleShape> _lines;
    int _pixelsPerSpace;

    sf::Vector2<int> nearestIntersection(int x, int y) const;
    void createLines();
};


#endif //GOMOKU_GRAPHICS_HPP
