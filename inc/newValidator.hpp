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
        _movers.emplace_back([](sf::Vector2i& v) { --v.x; }, [](sf::Vector2i& v) { ++v.x; });
        _movers.emplace_back([](sf::Vector2i& v) { --v.y; }, [](sf::Vector2i& v) { ++v.y; });
        _movers.emplace_back([](sf::Vector2i& v) { --v.x; --v.y; }, [](sf::Vector2i& v) { ++v.x; ++v.y; });
        _movers.emplace_back([](sf::Vector2i& v) { --v.x; ++v.y; }, [](sf::Vector2i& v) { ++v.x; --v.y; });
    }
    ~NewValidator() override = default;
    bool validate() override;
private:
    int isOpenThree(const sf::Vector2i& pos);
    bool openThreeInDirection(const std::pair<move_f, move_f>& moves, const sf::Vector2i& pos);

    std::vector<std::vector<Tile>> _b;
    Player _player;
    std::vector<std::pair<move_f, move_f>> _movers;
};


#endif //GOMOKU_NEWVALIDATOR_HPP
