#include "Graphics.hpp"
#include "Validator.hpp"
#include "Gomoku.hpp"

int main() {

    Graphics                    graphics{};
    Two                         two{};
    DoubleThreeCheck            doubleThreeCheck{two};
    Validator                   validator{doubleThreeCheck};
    Gomoku                      gomoku(validator, graphics);

    return 0;
}

