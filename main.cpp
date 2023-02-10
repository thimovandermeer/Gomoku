#include "Graphics.hpp"
#include "Validator.hpp"
#include "Gomoku.hpp"

int main() {

    Graphics graphics{};
    DoubleThreeCheck doubleThreeCheck{};
    Validator validator{doubleThreeCheck};
    Gomoku gomoku(validator, graphics);

    return 0;
}

