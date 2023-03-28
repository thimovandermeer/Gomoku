//
// Created by Thimo Van der meer on 27/03/2023.
//

#ifndef GOMOKU_BOARDSTATE_HPP
#define GOMOKU_BOARDSTATE_HPP
#include "Gomoku.hpp"
#include "Ai.hpp"

class BoardState {
public:
	std::vector<std::vector<Tile>> board;
	Tile player;

	BoardState(std::vector<std::vector<Tile>> board, Player player) :
	board(board), player((Tile)player)
	{
	}
	bool isValidMove(int row, int col);
	void makeMove(bestMove move);
	std::vector<bestMove> getValidMoves();
	bool isTerminal();
	void undoMove(bestMove move);

};

#endif //GOMOKU_BOARDSTATE_HPP
