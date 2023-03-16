//
// Created by Thimo Van der meer on 10/03/2023.
//

#include "Capture.hpp"
#include "logger.hpp"

Capture::Capture() {
    LOG("Capture constructor");
}

State Capture::CaptureCheck(const std::vector<Doubles>& doubles, const Coordinate& newCoords,
                            const std::vector<std::vector<Tile>>& board) {
    (void)doubles;
    (void)newCoords;
    (void)board;
    LOG("CaptureCheck");
    // if newCoords is a boundary of one of the doubles we need to check if the other boundary is also owned by the current player
    // if so this is a valid capture

    return {};
}