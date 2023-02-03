#include <iostream>
#include "inc/Graphics.hpp"
#include "inc/Validator.hpp"
#include "inc/Gomoku.hpp"

int main() {

    Graphics graphics{};
    Validator validator{};
    Gomoku gomoku(graphics, validator);

    return 0;
}

