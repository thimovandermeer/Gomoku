//
// Created by Thimo Van der meer on 27/03/2023.
//

#ifndef GOMOKU_AI_HPP
#define GOMOKU_AI_HPP
#include "types.hpp"
#include <vector>
#include "boardState.hpp"

struct bestMove;
struct AiResponse {
	std::string errorString;
	bestMove	move;
};

struct GameState {
	std::vector<std::vector<Tile>> board;
	Player currentPlayer = Player::PLAYERONE;
	int lastMoveRow = -1;
	int lastMoveCol = -1;
};

class IAi {
public:
	virtual ~IAi() = default;
	virtual AiResponse AiMove(const std::vector<std::vector<Tile>>& board,const Player &player) = 0;
};

class Ai : public IAi
{
public:
	explicit Ai(){};

	Ai(const Ai&) {};
	~Ai() override = default;

	AiResponse AiMove(const std::vector<std::vector<Tile>>& board,const Player &player) override;

	int evaluate(BoardState state);

private:
	bestMove miniMax(BoardState state, int depth, int alpha, int beta, bool maximizingPlayer);
	int evaluateOwnMoves(const std::vector<std::vector<Tile>> &board, Tile player);
	int evaluateOpponentMoves(const std::vector<std::vector<Tile>> &board, Tile player);
};


#endif //GOMOKU_AI_HPP
