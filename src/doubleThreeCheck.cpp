//
// Created by Thimo Van der meer on 09/02/2023.
//

#include "doubleThreeCheck.hpp"

void DoubleThreeCheck::DoubleThreeChecker(const std::vector<std::vector<Tile>> &board, const Coordinates &coord,
										  const Player &player)
{
	_board = board;
	_coord = coord;
	_player = player;
	std::string reason;
	_state = this->set_state(ACCEPTED, reason);
}

errorState DoubleThreeCheck::set_state(State newState, std::string &errorReason) {
	_state.error_reason = errorReason;
	_state.state = newState;
}
