//
// Created by Jonas Bennink Bolt on 2/3/23.
//

#ifndef GOMOKU_GOMOKU_HPP
#define GOMOKU_GOMOKU_HPP
#include <vector>
#include "Validator.hpp"
#include "Graphics.hpp"

enum class Tile{PLAYERONE, PLAYERTWO, FREE};

class IValidator;
class Gomoku {
    Gomoku();
    ~Gomoku() = default;

private:
    std::unique_ptr<IValidator> validator;
    std::unique_ptr<IGraphics> graphics;

    void updateBoardNegative();
    void updateBoardPositive();
    void doMove();
    void validateMove();
    std::vector<std::vector<Tile>> board;

};


#endif //GOMOKU_GOMOKU_HPP
