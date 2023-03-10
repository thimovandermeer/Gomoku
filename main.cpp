#include "Gomoku.hpp"

int main() {
    std::unique_ptr<IGraphics> graphics = std::make_unique<Graphics>();
    std::unique_ptr<ITwo> two_p1 = std::make_unique<Two>();
    std::unique_ptr<ITwo> two_p2 = std::make_unique<Two>();
    std::unique_ptr<IDoubleThreeCheck> doubleThreeCheck_p1 = std::make_unique<DoubleThreeCheck>(two_p1);
    std::unique_ptr<IDoubleThreeCheck> doubleThreeCheck_p2 = std::make_unique<DoubleThreeCheck>(two_p2);
    std::unique_ptr<IValidator> validator_p1 = std::make_unique<Validator>(doubleThreeCheck_p1);
    std::unique_ptr<IValidator> validator_p2 = std::make_unique<Validator>(doubleThreeCheck_p2);
    Gomoku gomoku(validator_p1, validator_p2, graphics);

    gomoku.gameLoop();

    return 0;
}

