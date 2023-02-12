//
// Created by Jonas Bennink Bolt on 2/3/23.
//

#ifndef GOMOKU_GOMOKU_HPP
#define GOMOKU_GOMOKU_HPP
#include <vector>
#include "Validator.hpp"
#include "Graphics.hpp"

#define BOARD_SIZE 19

class Gomoku {
public:
    Gomoku() = delete;
    Gomoku(const Gomoku&) = delete;
    Gomoku& operator=(const Gomoku&) = delete;
    ~Gomoku() = default;
    Gomoku(IValidator& validator, IGraphics& graphics) : _validator(validator.clone()), _graphics(graphics.clone()) {}

private:
    std::unique_ptr<IValidator> _validator;
    std::unique_ptr<IGraphics> _graphics;

    void updateBoardNegative();
    void updateBoardPositive();
    void doMove();
    void validateMove();
    std::vector<std::vector<Tile>> board;

};


#endif //GOMOKU_GOMOKU_HPP
