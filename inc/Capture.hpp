//
// Created by Thimo Van der meer on 10/03/2023.
//

#ifndef GOMOKU_CAPTURE_HPP
#define GOMOKU_CAPTURE_HPP

#include "types.hpp"
#include <vector>

class ICapture {
public:
    virtual ~ICapture() = default;
    virtual State CaptureCheck(const std::vector<Doubles>& doubles, const Coordinate& newCoords,
                               const std::vector<std::vector<Tile>>& board, const Player& player) = 0;
};

class Capture : public ICapture {
public:
    Capture();
    Capture(const Capture&) {};
    ~Capture() override = default;

    State CaptureCheck(const std::vector<Doubles>& doubles, const Coordinate& newCoords,
                       const std::vector<std::vector<Tile>>& board, const Player& player) override;

private:
    enum Orientation {
        LEFT, RIGHT
    };
    void isNewStoneBoundary(const Doubles& elem);
    void checkLeftBoundaryCapture(const Direction& direction, const Coordinate& boundaryCoords);
    void checkRightBoundaryCapture(const Direction& direction, const Coordinate& boundaryCoords);
    void setVariables(const std::vector<Doubles>& doubles, const Coordinate& newCoords,
                      const std::vector<std::vector<Tile>>& board, const Player& player);
    void boundaryTrue(Orientation orientation);
    void checkLeftBoundaryHorizontalCapture(const Coordinate& boundaryCoords);
    void checkLeftBoundaryVerticalCapture(const Coordinate& boundaryCoords);
    void checkLeftBoundaryCrossCapture(const Coordinate& boundaryCoords);

    void checkRightBoundaryHorizontalCapture(const Coordinate& boundaryCoords);
    void checkRightBoundaryVerticalCapture(const Coordinate& boundaryCoords);
    void checkRightBoundaryCrossCapture(const Coordinate& boundaryCoords);

    bool isOtherBoundarySameColor(const Doubles& elem);

    struct Boundary {
        bool is_boundary;
        Orientation orientation;
    };
    /*
     * vars
     */
    std::vector<Doubles> _doubles;
    Coordinate _newCoords;
    std::vector<std::vector<Tile>> _board;
    Boundary _boundary;
    Player _player;

};


#endif //GOMOKU_CAPTURE_HPP
