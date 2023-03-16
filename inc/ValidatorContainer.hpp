//
// Created by Thimo Van der meer on 16/03/2023.
//

#ifndef GOMOKU_VALIDATORCONTAINER_HPP
#define GOMOKU_VALIDATORCONTAINER_HPP

#include "types.hpp"
#include "Validator.hpp"

class IValidator;

class IValidatorContainer {
public:
    virtual ~IValidatorContainer() = default;
    virtual State p1Validate(const std::vector<std::vector<Tile>>& board, const Coordinate& coord, const Player& player) = 0;
    virtual State p2Validate(const std::vector<std::vector<Tile>>& board, const Coordinate& coord, const Player& player) = 0;
};

class ValidatorContainer : public IValidatorContainer {
public:
    explicit ValidatorContainer(std::unique_ptr<IValidator>& v_1, std::unique_ptr<IValidator>& v_2)
            :
            _p1(std::move(v_1)),
            _p2(std::move(v_2)) {}

    ~ValidatorContainer() override = default;

    State p1Validate(const std::vector<std::vector<Tile>>& board, const Coordinate& coord, const Player& player) override;
    State p2Validate(const std::vector<std::vector<Tile>>& board, const Coordinate& coord, const Player& player) override;
    std::vector<Doubles> getOpponentDoubleTwoList(Player player);

private:
    std::unique_ptr<IValidator> _p1;
    std::unique_ptr<IValidator> _p2;
};

#endif //GOMOKU_VALIDATORCONTAINER_HPP
