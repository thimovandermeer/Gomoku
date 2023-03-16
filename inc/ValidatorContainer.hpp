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
    virtual errorState p1_validate(const std::vector<std::vector<Tile>>& board, const Coordinates& coord, const Player& player) = 0;
    virtual errorState p2_validate(const std::vector<std::vector<Tile>>& board, const Coordinates& coord, const Player& player) = 0;
};

class ValidatorContainer : public IValidatorContainer {
public:
    explicit ValidatorContainer(std::unique_ptr<IValidator> &v_1, std::unique_ptr<IValidator> &v_2)
    :
        _p1(std::move(v_1)),
        _p2(std::move(v_2)) {}

    ~ValidatorContainer() override = default;

    errorState p1_validate(const std::vector<std::vector<Tile>>& board, const Coordinates& coord, const Player& player) override;
    errorState p2_validate(const std::vector<std::vector<Tile>>& board, const Coordinates& coord, const Player& player) override;
    std::vector<Doubles> get_opponent_double_two_list(Player player);

private:
    std::unique_ptr<IValidator> _p1;
    std::unique_ptr<IValidator> _p2;


};


#endif //GOMOKU_VALIDATORCONTAINER_HPP
