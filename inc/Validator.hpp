//
// Created by Jonas Bennink Bolt on 2/3/23.
//

#ifndef GOMOKU_VALIDATOR_HPP
#define GOMOKU_VALIDATOR_HPP

class IValidator {
public:
    bool validate();
};

class Validator : IValidator {
    Validator() = default;
    ~Validator() = default;

};


#endif //GOMOKU_VALIDATOR_HPP
