//
// Created by Thimo Van der meer on 27/03/2023.
//

#ifndef GOMOKU_BOARDSTATE_HPP
#define GOMOKU_BOARDSTATE_HPP
#include "Gomoku.hpp"
#include "Ai.hpp"

struct TileAi {
	Tile pos;
	bool Removable;
};

class BoardState {
public:
	std::vector<std::vector<TileAi>> board;
	Tile player = Tile::P2;
	Tile opponent = Tile::P1;
	BoardState(std::vector<std::vector<Tile>> board, Player player) :
	player((Tile)player)
	{
		setBoard(board);
	}
	bool isValidMove(int row, int col);
	bool makeMove(Coordinate move);
	std::vector<Coordinate> getValidMoves();
	bool isTerminal();
	void undoMove(bestMove move);
	void setBoard(std::vector<std::vector<Tile>> board);

};

#endif //GOMOKU_BOARDSTATE_HPP
