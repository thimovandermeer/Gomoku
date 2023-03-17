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
    virtual State CaptureCheck(const std::vector<Doubles> &doubles, const Coordinate &newCoords, const std::vector<std::vector<Tile>> &board,const Player &player) = 0;
};
class Capture: public ICapture {
public:
    Capture();
    Capture(const Capture&) {};
    ~Capture() override = default;

    State CaptureCheck(const std::vector<Doubles> &doubles, const Coordinate &newCoords, const std::vector<std::vector<Tile>> &board, const Player &player) override;

private:
    enum Orientation {LEFT, RIGHT};
    void    is_new_stone_boundary(const Doubles &elem);
    void    check_left_boundary_capture(const Direction &direction, const Coordinate &boundary_coords);
    void    check_right_boundary_capture(const Direction &direction, const  Coordinate &boundary_coords);
    void    set_variables(const std::vector<Doubles>& doubles, const Coordinate& newCoords,
                          const std::vector<std::vector<Tile>>& board, const Player &player);
    void    boundary_true(Orientation orientation);
    void check_left_boundary_horizontal_capture(const Coordinate &boundary_coords);
    void check_left_boundary_vertical_capture(const Coordinate &boundary_coords);
    void check_left_boundary_cross_capture(const Coordinate &boundary_coords);

    void check_right_boundary_horizontal_capture(const Coordinate &boundary_coords);
    void check_right_boundary_vertical_capture(const Coordinate &boundary_coords);
    void check_right_boundary_cross_capture(const Coordinate &boundary_coords);

    bool is_other_boundary_same_color(const Doubles &elem);

    struct Boundary {
        bool        is_boundary;
        Orientation orientation;
    };
    /*
     * vars
     */
    std::vector<Doubles>            _doubles;
    Coordinate                      _newCoords;
    std::vector<std::vector<Tile>>  _board;
    Boundary                        _boundary;
    Player                          _player;

};


#endif //GOMOKU_CAPTURE_HPP
