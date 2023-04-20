#include "Gomoku.hpp"
#include "Graphics.hpp"

int main() {
    std::unique_ptr<IGraphics> graphics = std::make_unique<Graphics>();
    std::unique_ptr<IAi> ai = std::make_unique<Ai>();
	Gomoku gomoku(graphics, ai);

    gomoku.gameLoop();

    return 0;
}
