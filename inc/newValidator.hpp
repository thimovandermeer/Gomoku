//
// Created by Jonas Bennink bolt on 3/30/23.
//

#ifndef GOMOKU_NEWVALIDATOR_HPP
#define GOMOKU_NEWVALIDATOR_HPP

#include "Gomoku.hpp"
#include "types.hpp"

class IValidator {
public:
    virtual ~IValidator() = default;
    virtual bool validate() = 0;
};

class NewValidator : public IValidator {
public:
    NewValidator() = delete;
    explicit NewValidator(const std::vector<std::vector<Tile>>& board, const Player& player) :
            _b(board), _player(player) {
        _movers.emplace_back([](Coordinate& v) { --v.x; }, [](Coordinate& v) { ++v.x; });
        _movers.emplace_back([](Coordinate& v) { --v.y; }, [](Coordinate& v) { ++v.y; });
        _movers.emplace_back([](Coordinate& v) { --v.x; --v.y; }, [](Coordinate& v) { ++v.x; ++v.y; });
        _movers.emplace_back([](Coordinate& v) { --v.x; ++v.y; }, [](Coordinate& v) { ++v.x; --v.y; });
    }
    ~NewValidator() override = default;
    bool validate() override;
private:
    int isOpenThree(const Coordinate& pos);
    bool
    openThreeInDirection(const std::pair<std::function<void(Coordinate&)>, std::function<void(Coordinate&)>>& moves,
                         const Coordinate& pos);

    std::vector<std::vector<Tile>> _b;
    Player _player;
    std::vector<std::pair<std::function<void(Coordinate&)>, std::function<void(Coordinate&)>>> _movers;
};


#endif //GOMOKU_NEWVALIDATOR_HPP
