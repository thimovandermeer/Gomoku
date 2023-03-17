//
// Created by Jonas Bennink Bolt on 2/3/23.
//

#ifndef GOMOKU_VALIDATOR_HPP
#define GOMOKU_VALIDATOR_HPP

#include <string>
#include <vector>
#include "DoubleThreeCheck.hpp"
#include "Capture.hpp"
#include "types.hpp"

class IValidator {
public:
    virtual ~IValidator() = default;
    virtual State validate(const std::vector<std::vector<Tile>>& board, const Coordinate& coord, const Player& player,
                           const std::vector<Doubles>& opponentDoubles) = 0;
    virtual std::vector<Doubles> getDoubleTwoList() = 0;
};

class IDoubleThreeCheck;

class Validator : public IValidator {
public:
    explicit Validator(std::unique_ptr<IDoubleThreeCheck>& DoubleThreeCheck, std::unique_ptr<ICapture>& Capture)
            : _coord{}, _player{}, _state{}, _doubleThreeCheck(std::move(DoubleThreeCheck)), _capture(std::move(Capture)) {}
    ~Validator() override = default;

    State validate(const std::vector<std::vector<Tile>>& board, const Coordinate& coord, const Player& player,
                   const std::vector<Doubles>& opponentDoubles) override;
    std::vector<Doubles> getDoubleTwoList() override;
private:
    void setData(const std::vector<std::vector<Tile>>& board, const Coordinate& coord, const Player& player);
    void setBoard(const std::vector<std::vector<Tile>>& board);
    void setCoordinates(const Coordinate& coord);
    void setPlayer(const Player& player);
    void setState(OkState newState, std::string& errorReason);
    void setOpponentDoubles(const std::vector<Doubles>& opponentDoubles);
    void boardValidation();
    void coordinatesValidation();
    void boundaryChecking();
    void takenCheck();
    void playerValidation();
    void doubleThreeValidation();
    void updateDoubleList();
    void captureValidation();
    std::vector<std::vector<Tile>> _board;
    Coordinate _coord;
    Player _player;
    State _state;
    std::vector<Doubles> _opponentDoubles;

    std::vector<Doubles> _doubleVector;
    std::unique_ptr<IDoubleThreeCheck> _doubleThreeCheck;
    std::unique_ptr<ICapture> _capture;
};

#endif //GOMOKU_VALIDATOR_HPP
