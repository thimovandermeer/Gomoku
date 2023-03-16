//
// Created by Thimo Van der meer on 16/03/2023.
//

#include "ValidatorContainer.hpp"

// TODO: REMOVE PLAYER FROM THIS STRUCT WE ALREADY KNOW WHAT IT IS
errorState ValidatorContainer::p1_validate(const std::vector<std::vector<Tile>>& board, const Coordinates& coord, const Player& player) {
    return (_p1->validate(board, coord, player, get_opponent_double_two_list(Player::PLAYERONE)));
}

errorState ValidatorContainer::p2_validate(const std::vector<std::vector<Tile>>& board, const Coordinates& coord, const Player& player) {
    return (_p2->validate(board, coord, player, get_opponent_double_two_list(Player::PLAYERTWO)));
}

std::vector<Doubles> ValidatorContainer::get_opponent_double_two_list(Player player) {
    if(player == Player::PLAYERONE) {
        return (_p2->get_double_two_list());
    } else {
        return (_p1->get_double_two_list());
    }
}