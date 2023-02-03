//
// Created by Jonas Bennink Bolt on 2/3/23.
//

#ifndef GOMOKU_GRAPHICS_HPP
#define GOMOKU_GRAPHICS_HPP

#include <iostream>

class IGraphics {
public:
    virtual ~IGraphics() = default;
    virtual bool updateBoardPositive() = 0;
    virtual bool updateBoardNegative() = 0;
};

class Graphics : public IGraphics {
public:
    Graphics() {std::cerr << "graphics ctor" << std::endl;}
    ~Graphics() override = default;
    bool updateBoardPositive() override;
    bool updateBoardNegative() override;

};


#endif //GOMOKU_GRAPHICS_HPP
