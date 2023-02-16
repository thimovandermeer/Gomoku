#include "Graphics.hpp"
#include "Validator.hpp"
#include "Gomoku.hpp"
#include "logger.hpp"

int main() {

	LOG("change type to EmptyGraphics if you don't want to start up the screen for now");
	Graphics                    graphics{};
    std::unique_ptr<ITwo>                         two = std::make_unique<Two>();
    std::unique_ptr<IDoubleThreeCheck>            doubleThreeCheck = std::make_unique<DoubleThreeCheck>(two);
    Validator                   validator{doubleThreeCheck};
    Gomoku                      gomoku(validator, graphics);

    return 0;
}

