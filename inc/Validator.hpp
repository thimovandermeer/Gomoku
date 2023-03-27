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
    virtual State validate(const std::vector<std::vector<Tile>>& board, const Coordinate& coord, const Player& player) = 0;
};

class IDoubleThreeCheck;

class Validator : public IValidator {
public:
    explicit Validator(std::unique_ptr<IDoubleThreeCheck>& DoubleThreeCheck, std::unique_ptr<ICapture>& Capture)
            :  _doubleThreeCheck(std::move(DoubleThreeCheck)), _capture(std::move(Capture)) {}
    ~Validator() override = default;

    State validate(const std::vector<std::vector<Tile>>& board, const Coordinate& coord, const Player& player) override;
private:
    void setState(OkState newState, std::string& errorReason);
    void boardValidation(const std::vector<std::vector<Tile>>& board);
    void coordinatesValidation(const Coordinate &coords);
    void boundaryChecking(const Coordinate &coords);
	void takenCheck(const std::vector<std::vector<Tile>>& board, const Coordinate& coord);
	void doubleThreeValidation(const std::vector<std::vector<Tile>>& board, const Coordinate& coord, const Player& player);
    void captureValidation(const std::vector<std::vector<Tile>>& board, const Coordinate& coord, const Player& player);
	void doubleThreeBreaksValidation(const std::vector<std::vector<Tile>>& board, const Doubles& capture_pos, const Player& player);
	State _state;
    std::unique_ptr<IDoubleThreeCheck> _doubleThreeCheck;
    std::unique_ptr<ICapture> _capture;
};

#endif //GOMOKU_VALIDATOR_HPP
