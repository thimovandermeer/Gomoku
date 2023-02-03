#include "Graphics.hpp"
#include "Validator.hpp"
#include "Gomoku.hpp"

int main() {

    Graphics graphics{};
    Validator validator{};
    Gomoku gomoku(validator, graphics);

    return 0;
}

