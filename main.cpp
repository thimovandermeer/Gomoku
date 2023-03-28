#include "Gomoku.hpp"
#include "Graphics.hpp"
#include "Validator.hpp"
#include "DoubleThreeCheck.hpp"


int main() {
    std::unique_ptr<IGraphics> graphics = std::make_unique<Graphics>();
	std::unique_ptr<IDoubleThreeCheck> doubleThreeCheck = std::make_unique<DoubleThreeCheck>();
	std::unique_ptr<ICapture> captureCheck = std::make_unique<Capture>();
    std::unique_ptr<IValidator> validator = std::make_unique<Validator>(doubleThreeCheck, captureCheck);
	std::unique_ptr<IAi> ai = std::make_unique<Ai>();
	Gomoku gomoku(validator, graphics, ai);

    gomoku.gameLoop();

    return 0;
}
