#include <iostream>
#include "Graphics.hpp"
#include "Validator.hpp"
#include "Gomoku.hpp"

int main() {

    Graphics graphics{};
    Validator validator{};
    Gomoku gomoku(graphics, validator);

    return 0;
}

