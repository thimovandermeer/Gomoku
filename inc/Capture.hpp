//
// Created by Thimo Van der meer on 10/03/2023.
//

#ifndef GOMOKU_CAPTURE_HPP
#define GOMOKU_CAPTURE_HPP
#include "types.hpp"

class ICapture {
public:
    virtual ~ICapture() = default;
    virtual State CaptureCheck(const std::vector<Doubles> &doubles, const Coordinate &newCoords, const std::vector<std::vector<Tile>> &board) = 0;
};
class Capture: public ICapture {
public:
    Capture();
    Capture(const Capture&) {};
    ~Capture() override = default;

    State CaptureCheck(const std::vector<Doubles> &doubles, const Coordinate &newCoords, const std::vector<std::vector<Tile>> &board) override;
};


#endif //GOMOKU_CAPTURE_HPP
