//
// Created by Jonas Bennink bolt on 3/30/23.
//

#include "NewValidator.hpp"
#include "logger.hpp"

enum Seq {
    OOB,
    EMPTY,
    P1,
    P2,
};

static bool isInBounds(const sf::Vector2i& pos) {
    return pos.x >= 0 && pos.x < BOARD_SIZE && pos.y >= 0 && pos.y < BOARD_SIZE;
}

// 4 is the start position
// * means it doesn't matter
// . means empty
// X means player to check

// * * . X X X .
// 0 1 2 3 4 5 6
static bool Pattern_xxx_(const std::vector<Seq>& sequence) {
    return sequence[2] == EMPTY &&
           sequence[6] == EMPTY &&
           sequence[3] == sequence[4] &&
           sequence[5] == sequence[4];
}

// . X X . X . *
// 0 1 2 3 4 5 6
static bool Pattern_xx_x_(const std::vector<Seq>& sequence) {
    return sequence[0] == EMPTY &&
           sequence[3] == EMPTY &&
           sequence[5] == EMPTY &&
           sequence[1] == sequence[4] &&
           sequence[2] == sequence[4];
}

// . X . X X . *
// 0 1 2 3 4 5 6
static bool Pattern_x_xx_(const std::vector<Seq>& sequence) {
    return sequence[0] == EMPTY &&
           sequence[2] == EMPTY &&
           sequence[5] == EMPTY &&
           sequence[1] == sequence[4] &&
           sequence[3] == sequence[4];
}

bool NewValidator::openThreeInDirection(const std::pair<move_f, move_f>& moves, const sf::Vector2i& pos) {
    sf::Vector2i current = pos;
    std::vector<Seq> sequence;
    // move 4 "left", in whatever of 4 directions it is
    for (int i = 0; i < 4; ++i) {
        moves.first(current);
    }

    // record 7 tiles in a row, with the 4th one being the location to check
    for (int i = 0; i < 7; ++i) {
        if (not isInBounds(current)) {
            sequence.push_back(OOB);
        } else {
            switch (_b[current.y][current.x]) {
                case Tile::P1:
                    sequence.push_back(P1);
                    break;
                case Tile::P2:
                    sequence.push_back(P2);
                    break;
                case Tile::EMPTY:
                    sequence.push_back(EMPTY);
                    break;
                default:
                    sequence.push_back(OOB);
                    break;
            }
        }
        moves.second(current);
    }

    // check 3 patterns
    if (Pattern_xxx_(sequence) || Pattern_xx_x_(sequence) || Pattern_x_xx_(sequence)) {
        return true;
    }
    return false;
}

int NewValidator::isOpenThree(const sf::Vector2i& pos) {
    int foundForMove = 0;
    for (const auto& movers: _movers) {
        if (openThreeInDirection(movers, pos)) {
            ++foundForMove;
        }
    }
    return foundForMove;
}

bool NewValidator::validate() {
    int openThreeCount = 0;
    Tile playerToCheck = _player == Player::PLAYERONE ? Tile::P1 : Tile::P2;
    for (unsigned int y = 0; y < _b.size(); ++y) {
        for (unsigned int x = 0; x < _b[y].size(); ++x) {
            // only check player that last moved
            if (_b[y][x] != playerToCheck) {
                continue;
            }
            openThreeCount += isOpenThree({static_cast<int>(x), static_cast<int>(y)});
            if (openThreeCount >= 2) {
                WARN("more than one open 3 for player %d", static_cast<int>(_player) + 1);
                return false;
            }
        }
    }
    return true;
}
