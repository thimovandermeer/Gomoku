//
// Created by Thimo Van der meer on 10/03/2023.
//

#include <gtest/gtest.h>
#include "Capture.hpp"
#include "utils.hpp"

// dit worden alleen maar Gmock like tests dus met I expect this function to be called once etc

auto captureLogic = Capture{};
TEST(capture_test, horizontal_capture) {

	// dit geeft twee coordinates terug die gecaptured moeten worden
	Coordinate new_coords;
	new_coords.y = 1;
	new_coords.x = 4;

	auto board = create_empty_board();
	// being captured
	board[1][2] = Tile::P1;
	board[1][3] = Tile::P1;

	// performing the capture
	board[1][1] = Tile::P2;
	board[1][4] = Tile::P2;

	auto result = captureLogic.CaptureCheck(new_coords,board, Player::PLAYERTWO);
	ASSERT_EQ(result.state, ACCEPTED);
	ASSERT_EQ(result.errorReason, "Valid horizontal capture");
}


TEST(capture_test, vertical_capture) {

	// dit geeft twee coordinates terug die gecaptured moeten worden
	Coordinate new_coords;
	new_coords.y = 4;
	new_coords.x = 1;

	auto board = create_empty_board();
	// being captured
	board[2][1] = Tile::P1;
	board[3][1] = Tile::P1;

	// performing the capture
	board[1][1] = Tile::P2;
	board[4][1] = Tile::P2;

	auto result = captureLogic.CaptureCheck(new_coords,board, Player::PLAYERTWO);
	ASSERT_EQ(result.state, ACCEPTED);
	ASSERT_EQ(result.errorReason, "Valid vertical capture");
}

TEST(capture_test, diagonal_capture) {

	// dit geeft twee coordinates terug die gecaptured moeten worden
	Coordinate new_coords;
	new_coords.y = 4;
	new_coords.x = 3;

	auto board = create_empty_board();
	// being captured
	board[2][1] = Tile::P1;
	board[3][2] = Tile::P1;

	// performing the capture
	board[1][0] = Tile::P2;
	board[4][3] = Tile::P2;

	auto result = captureLogic.CaptureCheck(new_coords,board, Player::PLAYERTWO);
	ASSERT_EQ(result.state, ACCEPTED);
	ASSERT_EQ(result.errorReason, "Valid diagonal capture");
}

