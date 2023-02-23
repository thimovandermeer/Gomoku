#include "Graphics.hpp"
#include "Validator.hpp"
#include "Gomoku.hpp"

int main() {

    std::unique_ptr<IGraphics> graphics = std::make_unique<Graphics>();
    std::unique_ptr<ITwo> two = std::make_unique<Two>();
    std::unique_ptr<IDoubleThreeCheck> doubleThreeCheck = std::make_unique<DoubleThreeCheck>(two);
    std::unique_ptr<IValidator> validator = std::make_unique<Validator>(doubleThreeCheck);

    Gomoku gomoku(validator, graphics);

    gomoku.gameLoop();

    return 0;
}

