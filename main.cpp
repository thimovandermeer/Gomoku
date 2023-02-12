#include "Graphics.hpp"
#include "Validator.hpp"
#include "Gomoku.hpp"
#include "logger.hpp"

int main() {

    LOG("change type to EmptyGraphics if you don't want to start up the screen for now");
    Graphics graphics{};
    DoubleThreeCheck doubleThreeCheck{};
    Validator validator{doubleThreeCheck};
    Gomoku gomoku(validator, graphics);

    return 0;
}

