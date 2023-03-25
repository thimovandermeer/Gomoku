#include "Gomoku.hpp"
#include "Graphics.hpp"
#include "Validator.hpp"
#include "DoubleThreeCheck.hpp"

int main() {
    std::unique_ptr<IGraphics> graphics = std::make_unique<Graphics>();
	std::unique_ptr<IDoubleThreeCheck> doubleThreeCheck = std::make_unique<DoubleThreeCheck>();
	std::unique_ptr<ICapture> captureCheck = std::make_unique<Capture>();
    std::unique_ptr<IValidator> validator = std::make_unique<Validator>(doubleThreeCheck, captureCheck);
	Gomoku gomoku(validator, graphics);

    gomoku.gameLoop();

    return 0;
}
