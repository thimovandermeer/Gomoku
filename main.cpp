#include "Graphics.hpp"
#include "Validator.hpp"
#include "Gomoku.hpp"

int main() {

    Graphics graphics{};
    Validator validator{};
    std::cerr << "ptr in main " << &graphics << std::endl;
    Gomoku gomoku(&validator, &graphics);

    return 0;
}

