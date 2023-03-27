//
// Created by Thimo Van der meer on 09/02/2023.
//

#include "DoubleThreeCheck.hpp"
#include "logger.hpp"
#include "Gomoku.hpp"
#include "utils.hpp"

void DoubleThreeCheck::doubleThreeBreaks(const std::vector<std::vector<Tile>>& board, const Doubles& capture_pos, const Player& player) {
	// check opposite player
	Player opposite_player;
	if(player == Player::PLAYERONE) {
		opposite_player = Player::PLAYERTWO;
	} else {
		opposite_player = Player::PLAYERONE;
	}
	auto result = doubleThreeCheckLogic(capture_pos.one, (Tile) opposite_player, board);
	if(result > 0) {
		if(opposite_player == Player::PLAYERONE) {
			p1_doubleThreeExists--;
		} else {
			p2_doubleThreeExists--;
		}
	}

	auto second_result = doubleThreeCheckLogic(capture_pos.two, (Tile) player, board);
	if(second_result > 0) {
		if(player == Player::PLAYERONE) {
			p1_doubleThreeExists--;
		} else if(player == Player::PLAYERTWO) {
			p2_doubleThreeExists--;
		}
	}

	if(p1_doubleThreeExists < 0 || p2_doubleThreeExists < 0) {
		ERROR("FATAL ERROR size of double three is smaller than 0");
	}
}

int DoubleThreeCheck::checkHorizontal(const Coordinate &coords, Tile player, const std::vector<std::vector<Tile>> &board)
{
	int count = 0;
	LOG("Check horizontal");
	LOG("y coordinaten %i X coordinaten %i", coords.y, coords.x);
	for (int i = coords.x-3; i <= coords.x+3; i++) {
		// check board boundaries
		LOG("Kom ik in de eerste check");
		if(i >= 0 && i+3 < BOARD_SIZE) {
			LOG("Kom ik in de tweede check");
			// check if we have three in line
			if (board[coords.y][i] == player && board[coords.y][i+1] == player && board[coords.y][i+2] == player) {
				LOG("We got three in a row");
				if (board[coords.y][i+3] == Tile::EMPTY) {
					LOG("We got a regular three in a row horizontal");
					count++;
				}
			}
			// double three with open space afmaken
			if(board[coords.y][i] == player && board[coords.y][i+1] == player && board[coords.y][i+2] == Tile::EMPTY && board[coords.y][i+3] == player) {
				LOG("We got a double three with empty space");
				count++;
			}
		}
	}
	return count;
}

int DoubleThreeCheck::checkVertical(const Coordinate &coords, Tile player, const std::vector<std::vector<Tile>> &board)
{
	LOG("Check vertical");
	int count = 0;
	for (int j = coords.y-3; j <= coords.y+3; j++) {
		if(j >= 0 && j+3 < BOARD_SIZE) {
			if(board[j][coords.x] == player && board[j+1][coords.x] == player && board[j+2][coords.x] == player) {
				LOG("We have three in a row");
				if(board[j+3][coords.x] == Tile::EMPTY) {
					LOG("We got a regular three in a row vertical");
					count++;
				}
			}
			// double three with open space
			if(board[j][coords.x] == player && board[j+1][coords.x] == player && board[j+2][coords.x] == Tile::EMPTY && board[j+3][coords.x] == player) {
				LOG("We got a double three with empty space");
				count++;
			}
		}
	}
	return count;
}

int DoubleThreeCheck::checkDiagonal(const Coordinate &coords, Tile player, const std::vector<std::vector<Tile>> &board)
{
	LOG("Check diagonal");
	int count = 0;
	for (int i = coords.x-3, j = coords.y-3; i <= coords.x+3 && j <= coords.y+3; i++, j++) {
		if(i >= 0 && i+3 < BOARD_SIZE && j >= 0 && j+3 < BOARD_SIZE) {
			if(board[j][i] == player && board[j+1][i+1] == player && board[j+2][i+2] == player) {
				LOG("Three in a row found");
				if(board[j+3][i+3] == Tile::EMPTY) {
					LOG("Regular three in a row diagonal found");
					count++;
				}
			}
			if(board[j][i] == player && board[j+1][i+1] == player && board[j+2][i+2] == Tile::EMPTY && board[j+3][i+3] == player) {
				LOG("We got a double three with empty space diagonal");
				count++;
			}

		}
	}
	return count;
}

int DoubleThreeCheck::checkAntiDiagonal(const Coordinate &coords, Tile player,
										const std::vector<std::vector<Tile>> &board)
{
	LOG("Check anti diagonal");
	int count = 0;
	for (int i = coords.x+3, j = coords.y-3; i >= coords.x-3 && j <= coords.y+3; i--, j++) {
		if(i >= 0 && i-3 < BOARD_SIZE && i-5> 0&& j >= 0 && j+3 < BOARD_SIZE && i < BOARD_SIZE) {
			if(board[j][i] == player && board[j+1][i-1] == player && board[j+2][i-2] == player) {
				LOG("Found three in a row");
				if(board[j+3][i-3] == Tile::EMPTY) {
					LOG("Found regular three in a row anti diagonal");
					count++;
				}
			}
			if(board[j][i] == player && board[j+1][i-1] == player && board[j+2][i-2] == Tile::EMPTY && board[j+3][i-3] == player) {
				LOG("We got a double three with empty space anti diagonal");
				count++;
			}
		}
	}
	return count;
}
int DoubleThreeCheck::doubleThreeCheckLogic(const Coordinate &coords, Tile player, const std::vector<std::vector<Tile>> &board) {
	int count = 0;

	// check horizontal
	count += checkHorizontal(coords, player, board);
	// check vertical
	count += checkVertical(coords,player, board);
	// check diagonal
	count += checkDiagonal(coords,player,board);
	// check anti-diagonal
	count += checkAntiDiagonal(coords,player,board);

	if(count == 1) {
		LOG("We found one double three");
		return count;
	} if(count > 1) {
		LOG("We found multiple double three");
		return count;
	}
	return count;
}


State DoubleThreeCheck::DoubleThreeChecker(const std::vector<std::vector<Tile>>& board, const Coordinate& newCoord,
                                           const Player& player)
{
	State 	returnValue;
	Tile 	player_board;
	int		playerThree;
	if(player == Player::PLAYERONE) {
		player_board = Tile::P1;
		playerThree = p1_doubleThreeExists;
	} else {
		player_board = Tile::P2;
		playerThree = p2_doubleThreeExists;
	}
	auto result = doubleThreeCheckLogic(newCoord, player_board, board);
	if(result > 0 && result < 2 && playerThree < 1) {
		playerThree++;

		returnValue.state = OkState::ACCEPTED;
		returnValue.errorReason = "FIRST DOUBLE THREE";
		if(player == Player::PLAYERONE) {
			p1_doubleThreeExists = playerThree;
		} else {
			p2_doubleThreeExists = playerThree;
		}
		return returnValue;
	} else if(result > 1 || (result == 1 && playerThree == 1)) {
		returnValue.state = OkState::ERROR;
		returnValue.errorReason = "SECOND DOUBLE THREE";
		if(player == Player::PLAYERONE) {
			p1_doubleThreeExists = playerThree;
		} else {
			p2_doubleThreeExists = playerThree;
		}
		return returnValue;
	}
	returnValue.state = OkState::ACCEPTED;
	returnValue.errorReason = "NO DOUBLE THREE FOUND";
	if(player == Player::PLAYERONE) {
		p1_doubleThreeExists = playerThree;
	} else {
		p2_doubleThreeExists = playerThree;
	}
	return returnValue;
}


