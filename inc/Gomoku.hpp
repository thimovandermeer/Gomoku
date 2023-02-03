//
// Created by Jonas Bennink Bolt on 2/3/23.
//

#ifndef GOMOKU_GOMOKU_HPP
#define GOMOKU_GOMOKU_HPP
#include <vector>
#include "Validator.hpp"
#include "Graphics.hpp"


enum class tile{PLAYERONE, PLAYERTWO, FREE};

class Gomoku {
    Gomoku();
    ~Gomoku() = default;

private:
    IValidator validator;
    IGraphics graphics;

    void updateBoardNegative();
    void updateBoardPositive();
    void doMove();
    void validateMove();
    std::vector<std::vector<tile>> board;

};


#endif //GOMOKU_GOMOKU_HPP
