//
// Created by Jonas Bennink Bolt on 2/3/23.
//

#ifndef GOMOKU_GRAPHICS_HPP
#define GOMOKU_GRAPHICS_HPP

#include <memory>
#include <SFML/Graphics.hpp>

// game becomes near unplayable if BOARD_SIZE * 10 >= WINDOW_WIDTH
#define WINDOW_WIDTH 750
#define WINDOW_HEIGHT (WINDOW_WIDTH * 1.1f)
#define CIRCLE_SCALE 0.75f

class IGraphics {
public:
    virtual ~IGraphics() = default;
    virtual bool updateBoardPositive() = 0;
    virtual bool updateBoardNegative() = 0;
};

class EmptyGraphics : public IGraphics {
public:
    bool updateBoardPositive() override { return false; }
    bool updateBoardNegative() override { return false; }
};

class Graphics : public IGraphics {
public:
    Graphics();
    Graphics(const Graphics&) = delete;
    Graphics& operator=(const Graphics&) = delete;
    ~Graphics() override = default;

    bool updateBoardPositive() override;
    bool updateBoardNegative() override;

private:
    std::vector<sf::CircleShape> _stones;

// these are (likely) set only once
    std::unique_ptr<sf::RenderWindow> _window;
    sf::Font _font;
    std::vector<int> _xCoordinates;
    std::vector<int> _yCoordinates;
    std::vector<sf::RectangleShape> _lines;
    int _pixelsPerSpace;

    sf::Text tempTitle(const std::unique_ptr<sf::RenderWindow>& window);
    sf::Vector2<int> nearestIntersection(int x, int y) const;
    void createLines();
};


#endif //GOMOKU_GRAPHICS_HPP
