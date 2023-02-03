//
// Created by Jonas Bennink Bolt on 2/3/23.
//

#ifndef GOMOKU_GRAPHICS_HPP
#define GOMOKU_GRAPHICS_HPP


class IGraphics {
public:
    virtual bool updateBoardPositive() = 0;
    virtual bool updateBoardNegative() = 0;
};

class Graphics : IGraphics {
    bool updateBoardPositive() override;
    bool updateBoardNegative() override;

};


#endif //GOMOKU_GRAPHICS_HPP
