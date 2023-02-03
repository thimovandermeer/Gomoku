//
// Created by Jonas Bennink Bolt on 2/3/23.
//

#include "Gomoku.hpp"


void Gomoku::updateBoardNegative() {
    _graphics->updateBoardNegative();
}

void Gomoku::updateBoardPositive() {
    _graphics->updateBoardPositive();
}

void Gomoku::doMove() {

}

void Gomoku::validateMove() {
    _validator->validate();
}
