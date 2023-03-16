//
// Created by Thimo Van der meer on 09/02/2023.
//

#ifndef GOMOKU_DOUBLETHREECHECK_HPP
#define GOMOKU_DOUBLETHREECHECK_HPP

#include <memory>
#include <string>
#include <vector>
#include "Two.hpp"
#include "types.hpp"

class ITwo;

class IDoubleThreeCheck {
public:
    virtual ~IDoubleThreeCheck() = default;
    virtual State
    DoubleThreeChecker(const std::vector<std::vector<Tile>>& board, const Coordinate& coord, const Player& player) = 0;
    virtual std::vector<Doubles> getDoubleTwo() = 0;
};

class DoubleThreeCheck : public IDoubleThreeCheck {
public:
    explicit DoubleThreeCheck(std::unique_ptr<ITwo>& Two) : _doubleThreeVector{}, _doubleTwoVector{}, _state{}, _two(std::move(Two)), _fullFrees(0) {}
    DoubleThreeCheck(const DoubleThreeCheck&) : _state{}, _fullFrees{} {}
    ~DoubleThreeCheck() override = default;

    static Threes fillDoubleThreeStack(Coordinate boundCoordinates, Coordinate newCoords, BoundaryCheckReturn type,
                                       bool left, Direction dir);
    void setBoard(const std::vector<std::vector<Tile>>& board);
    size_t doubleTwoSize();
    State DoubleThreeChecker(const std::vector<std::vector<Tile>>& board, const Coordinate& newCoord,
                             const Player& player) override;
    bool findThree(Coordinate newCoords, std::vector<Doubles>& doubleTwo);
//    State findDoubleThree();


    bool twoInARow(const std::vector<std::vector<Tile>>& board, const Coordinate& coord, const Player& play);
    Threes getLastThree();
    bool fullFreeCheck();

    std::vector<Doubles> getDoubleTwo() override;
private:
    void setState(OkState newState, std::string& errorReason);
    std::vector<Threes> _doubleThreeVector;
    std::vector<Doubles> _doubleTwoVector;
    State _state;
    std::shared_ptr<ITwo> _two;
    std::vector<std::vector<Tile>> _board;
    int _fullFrees;
};


#endif //GOMOKU_DOUBLETHREECHECK_HPP
