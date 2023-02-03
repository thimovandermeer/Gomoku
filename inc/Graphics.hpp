//
// Created by Jonas Bennink Bolt on 2/3/23.
//

#ifndef GOMOKU_GRAPHICS_HPP
#define GOMOKU_GRAPHICS_HPP
#include <memory>

class IGraphics {
public:
    virtual ~IGraphics() = default;
    virtual std::unique_ptr<IGraphics> clone() const = 0;
    virtual bool updateBoardPositive() = 0;
    virtual bool updateBoardNegative() = 0;
};

class Graphics : public IGraphics {
public:
    Graphics();
    Graphics(const Graphics&) = default;
    Graphics& operator=(const Graphics&) = delete;
    ~Graphics() override = default;
    std::unique_ptr<IGraphics> clone() const override {
        return std::make_unique<Graphics>(*this);
    }

    bool updateBoardPositive() override;
    bool updateBoardNegative() override;

};


#endif //GOMOKU_GRAPHICS_HPP
