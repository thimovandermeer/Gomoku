//
// Created by Jonas Bennink Bolt on 2/3/23.
//

#include "Gomoku.hpp"


Gomoku::Gomoku() = default;

void Gomoku::updateBoardNegative() {
    graphics.updateBoardNegative();
}

void Gomoku::updateBoardPositive() {
    graphics.updateBoardPositive();
}

void Gomoku::doMove() {

}

void Gomoku::validateMove() {
    validator.validate();
}

