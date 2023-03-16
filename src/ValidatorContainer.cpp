//
// Created by Thimo Van der meer on 16/03/2023.
//

#include "ValidatorContainer.hpp"

// TODO: REMOVE PLAYER FROM THIS STRUCT WE ALREADY KNOW WHAT IT IS
State ValidatorContainer::p1Validate(const std::vector<std::vector<Tile>>& board, const Coordinate& coord, const Player& player) {
    return (_p1->validate(board, coord, player, getOpponentDoubleTwoList(Player::PLAYERONE)));
}

State ValidatorContainer::p2Validate(const std::vector<std::vector<Tile>>& board, const Coordinate& coord, const Player& player) {
    return (_p2->validate(board, coord, player, getOpponentDoubleTwoList(Player::PLAYERTWO)));
}

std::vector<Doubles> ValidatorContainer::getOpponentDoubleTwoList(Player player) {
    if (player == Player::PLAYERONE) {
        return (_p2->getDoubleTwoList());
    } else {
        return (_p1->getDoubleTwoList());
    }
}