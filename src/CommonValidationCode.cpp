//
// Created by Thimo Van der meer on 16/03/2023.
//

#include "CommonValidationCode.hpp"
#include "logger.hpp"
#include <vector>

boundary_check_return check_right_boundary(Coordinates boundary_coords, Coordinates new_coords, Direction direction, const std::vector<std::vector<Tile>> &board) {
    LOG("boundary_coords in right boundary checking %i %i", boundary_coords.y, boundary_coords.x);
    LOG("Wat is de DIR %i", direction);
    boundary_check_return result{};
    if(direction == HORIZONTAL) {
        auto  three_type = check_right_boundary_horizontal(boundary_coords, new_coords, board);
        result.doubleType = three_type;
        result.openSpace = Coordinates{-1, -1};
        if(three_type == EMPTYSPACE) {
            auto open_space_coords = new_coords;
            open_space_coords.x = new_coords.x -1;
            result.openSpace = open_space_coords;
            result.doubleType = three_type;
        }
        LOG("IK RETURN HORIZONTAL");
        return result;
    } else if(direction == VERTICAL) {
        auto three_type = check_right_boundary_vertical(boundary_coords, new_coords, board);
        LOG("THREE TYPE = %I", three_type);
        result.doubleType = three_type;
        result.openSpace = Coordinates{-1,-1};
        if(three_type == EMPTYSPACE) {
            auto open_space_coords = new_coords;
            open_space_coords.y = new_coords.y - 1;
            result.openSpace = open_space_coords;
            result.doubleType = three_type;
        }
        LOG("WAT RETURN IK UBERHAUPT %i", result);
        LOG("IK RETURN VERTICAL");
        return result;
    } else if(direction == CROSS) {
        auto three_type = check_right_boundary_cross(boundary_coords, new_coords, board);
        result.doubleType = three_type;
        result.openSpace = Coordinates{-1,-1};
        if(three_type == EMPTYSPACE) {
            auto open_space_coords = new_coords;
            open_space_coords.y = new_coords.y - 1;
            open_space_coords.x = new_coords.x - 1;
            result.openSpace = open_space_coords;
            result.doubleType = three_type;
            return result;
        }
        LOG("IK RETURN CROSS");
        return result;
    }
    result.doubleType = NONE;
    result.openSpace = Coordinates{-1,-1};
    LOG("Did not access any right boundary direction checks");
    return result;
}

double_type			check_right_boundary_horizontal(Coordinates boundary_coords, Coordinates new_coords, const std::vector<std::vector<Tile>> &board)
{
    if(new_coords.y == boundary_coords.y) {
        LOG("We are on the same horizontal axis");
        if(new_coords.x - boundary_coords.x == 1) {
            LOG("Matching new[%i] boundary[%i]", new_coords.x, boundary_coords.x);
            return NORMAL;
        } if(new_coords.x - boundary_coords.x == 2) {
            LOG("Potentially one empty space in between");
            auto open_space_coords = new_coords;
            open_space_coords.x = new_coords.x - 1;
            LOG("OPEN space coords = %i", open_space_coords.x);
            if(open_space_is_empty(open_space_coords, board)) {
                LOG("Match horizontal we create double three with empty space in the middle new[%i] boundary[%i]", new_coords.x, new_coords.y);
                return EMPTYSPACE;
            } else {
                LOG("The space in between was not empty");
                return NONE;
            }
        }
        LOG("We are on the same horizontal axis but not in line new[%i] boundary[%i]", new_coords.x, boundary_coords.x);
        return NONE;
    }
    return NONE;
}

double_type		check_right_boundary_vertical(Coordinates boundary_coords, Coordinates new_coords, const std::vector<std::vector<Tile>> &board) {
    if(new_coords.x == boundary_coords.x){
        LOG("We are on the same vertical axis");
        if(new_coords.y - boundary_coords.y == 1) {
            LOG("Matching new[%i] boundary[%i]", new_coords.y, boundary_coords.y);
            return NORMAL;
        } if(new_coords.y - boundary_coords.y == 2) {
            LOG("new coords y = %i boundary coords y", new_coords.y, boundary_coords.y);
            auto open_space_coords = new_coords;
            open_space_coords.y = new_coords.y - 1;
            LOG("OPEN space coords = %i", open_space_coords.x);
            if(open_space_is_empty(open_space_coords, board)) {
                LOG("Match horizontal we create double three with empty space in the middle new[%i] boundary[%i]", new_coords.x, new_coords.y);
                return EMPTYSPACE;
            } else {
                LOG("The space in between was not empty");
                return NONE;
            }
        }
        LOG("We are on the same vertical axis but not in line new[%i] boundary[%i]", new_coords.y, boundary_coords.y);
        return NONE;
    }
    LOG("ERROR FOUND");
    return NONE;
}

double_type		check_right_boundary_cross(Coordinates boundary_coords, Coordinates new_coords, const std::vector<std::vector<Tile>> &board) {
    LOG("New coords y = %i", new_coords.y);
    LOG("boundary coords y = %i", boundary_coords.y);
    if((new_coords.y - boundary_coords.y) == 1) {
        LOG("The new y coords are one layer above boundary coords new[%i] boundary[%i]", new_coords.y, boundary_coords.y);
        if(new_coords.x - boundary_coords.x == 1) {
            LOG("the new x coords are one layer to the right from boundary coords new[%i] boundary[%i]", new_coords.x, boundary_coords.x);
            return NORMAL;
        }
        LOG("The new x coords are not in line with the boundary coords  coords new[%i] boundary[%i]", new_coords.x, boundary_coords.x);
        return NONE;
    } else if ((new_coords.y - boundary_coords.y) == 2) {
        LOG("Potentially one empty space in between");
        auto open_space_coords = new_coords;
        open_space_coords.y = new_coords.y - 1;
        open_space_coords.x = new_coords.x - 1;
        LOG("OPEN space coords = %i", open_space_coords.x);
        if(open_space_is_empty(open_space_coords, board)) {
            LOG("Match horizontal we create double three with empty space in the middle new[%i] boundary[%i]", new_coords.x, new_coords.y);
            return EMPTYSPACE;
        } else {
            LOG("The space in between was not empty");
            return NONE;
        }
    }
    LOG("The new coords are not in line with the boundary coords new[%i] boundary[%i]", new_coords.y, boundary_coords.y);
    return NONE;
}

double_type			check_left_boundary_horizontal(Coordinates boundary_coords,
                                                                        Coordinates new_coords, const std::vector<std::vector<Tile>> &board)
{
    if(new_coords.y == boundary_coords.y) {
        LOG("We are on the same horizontal axis");
        if(new_coords.x - boundary_coords.x == -1) {
            LOG("Matching new[%i] boundary[%i]", new_coords.x, boundary_coords.x);
            return NORMAL;
        } if(new_coords.x - boundary_coords.x == -2) {
            LOG("new coords x = %i boundary coords x = %i", new_coords.x, new_coords.y);
            auto open_space_coords = new_coords;
            open_space_coords.x = new_coords.x + 1;
            LOG("OPEN space coords = %i", open_space_coords.x);
            if(open_space_is_empty(open_space_coords, board)) {
                LOG("Match horizontal we create double three with empty space in the middle new[%i] boundary[%i]", new_coords.x, new_coords.y);
                return EMPTYSPACE;
            } else {
                LOG("The space in between was not empty");
                return NONE;
            }
        }
         return NONE;
    }
    return NONE;
}

double_type			check_left_boundary_vertical(Coordinates boundary_coords, Coordinates new_coords, const std::vector<std::vector<Tile>> &board)
{
    if(new_coords.x == boundary_coords.x){
        LOG("We are on the same vertical axis");
        if(new_coords.y - boundary_coords.y == -1) {
            LOG("Matching new[%i] boundary[%i]", new_coords.y, boundary_coords.y);
            return NORMAL;
        } if (new_coords.y - boundary_coords.y == -2) {
            LOG("Potentially one empty space in between");
            auto open_space_coords = new_coords;
            open_space_coords.y = new_coords.y + 1;
            LOG("OPEN space coords = %i", open_space_coords.x);
            if(open_space_is_empty(open_space_coords, board)) {
                LOG("Match horizontal we create double three with empty space in the middle new[%i] boundary[%i]", new_coords.x, new_coords.y);
                return EMPTYSPACE;
            } else {
                LOG("The space in between was not empty");
                return NONE;
            }
        }
        LOG("We are on the same vertical axis but not in line new[%i] boundary[%i]", new_coords.y, boundary_coords.y);
        return NONE;
    }
    return NONE;
}

double_type		check_left_boundary_cross(Coordinates boundary_coords, Coordinates new_coords, const std::vector<std::vector<Tile>> &board)
{
    LOG("new coords y %i boundary_coors y %i ", new_coords.y, boundary_coords.y);
    if((new_coords.y - boundary_coords.y) == -1) {
        LOG("The new y coords are one layer above boundary coords new[%i] boundary[%i]", new_coords.y, boundary_coords.y);
        if(new_coords.x - boundary_coords.x == -1) {
            LOG("the new x coords are one layer to the right from boundary coords new[%i] boundary[%i]", new_coords.x, boundary_coords.x);
            LOG("We are a match");
            return NORMAL;
        }
        LOG("The new x coords are not in line with the boundary coords  coords new[%i] boundary[%i]", new_coords.x, boundary_coords.x);
        return NONE;
    }
    else if ((new_coords.y - boundary_coords.y) == -2) {
        LOG("Potentially one empty space in between");
        auto open_space_coords = new_coords;
        open_space_coords.y = new_coords.y + 1;
        open_space_coords.x = new_coords.x + 1;
        LOG("OPEN space coords = %i", open_space_coords.x);
        if(open_space_is_empty(open_space_coords, board)) {
            LOG("Match horizontal we create double three with empty space in the middle new[%i] boundary[%i]", new_coords.x, new_coords.y);
            return EMPTYSPACE;
        } else {
            LOG("The space in between was not empty");
            return NONE;
        }
    }
    return NONE;
}


boundary_check_return check_left_boundary(Coordinates boundary_coords, Coordinates new_coords, Direction direction, const std::vector<std::vector<Tile>> &board) {
    LOG("boundary_coords in left boundary checking %i %i", boundary_coords.y, boundary_coords.x);
    LOG("Direction = %i", direction);
    boundary_check_return result{};
    if(direction == HORIZONTAL) {
        auto three_type = check_left_boundary_horizontal(boundary_coords, new_coords, board);
        result.doubleType = three_type;
        result.openSpace = Coordinates{-1,-1};
        if(three_type == EMPTYSPACE) {
            auto open_space_coords = new_coords;
            open_space_coords.x = new_coords.x + 1;
            result.openSpace = open_space_coords;
            result.doubleType = three_type;
        }
        return result;
    } else if(direction == VERTICAL) {
        auto three_type = check_left_boundary_vertical(boundary_coords, new_coords, board);
        result.doubleType = three_type;
        result.openSpace = Coordinates{-1,-1};
        if (three_type == EMPTYSPACE) {
            auto open_space_coords = new_coords;
            open_space_coords.y = new_coords.y + 1;
            result.openSpace = open_space_coords;
            result.doubleType = three_type;
        }
        return result;
    } else if(direction == CROSS) {
        auto three_type = check_left_boundary_cross(boundary_coords, new_coords, board);
        result.doubleType = three_type;
        result.openSpace = Coordinates{-1,-1};
        if(three_type == EMPTYSPACE) {
            auto open_space_coords = new_coords;
            open_space_coords.y = new_coords.y + 1;
            open_space_coords.x = new_coords.x + 1;
            result.openSpace = open_space_coords;
            result.doubleType = three_type;
        }
        return result;
        LOG("The new coords are not in line with the boundary coords new[%i] boundary[%i]", new_coords.y, boundary_coords.y);
    }
    result.doubleType = NONE;
    result.openSpace = Coordinates{-1,-1};
    return result;
}

bool check_free_left(Coordinates left_boundary, Direction dir,const  std::vector<std::vector<Tile>> &board) {
    if(dir == HORIZONTAL) {
        if(board[left_boundary.y][left_boundary.x - 1] == Tile::EMPTY) {
            return true;
        }else {
            return false;
        }
    }
    if(dir == VERTICAL) {
        if(board[left_boundary.y - 1][left_boundary.x] == Tile::EMPTY) {
            return true;
        }else {
            return false;
        }
    }
    if(dir == CROSS) {
        if(board[left_boundary.y - 1][left_boundary.x -1] == Tile::EMPTY) {
            return true;
        }else {
            return false;
        }
    }
}

bool check_free_right(Coordinates right_boundary, Direction dir, const std::vector<std::vector<Tile>> &board) {
    if(dir == HORIZONTAL) {
        if(board[right_boundary.y][right_boundary.x + 1] == Tile::EMPTY) {
            return true;
        }else {
            return false;
        }
    }
    if(dir == VERTICAL) {
        if(board[right_boundary.y + 1][right_boundary.x] == Tile::EMPTY) {
            return true;
        }else {
            return false;
        }
    }
    if(dir == CROSS) {
        if(board[right_boundary.y + 1][right_boundary.x + 1] == Tile::EMPTY) {
            return true;
        }else {
            return false;
        }
    }
}

bool		open_space_is_empty(Coordinates empty_space, const std::vector<std::vector<Tile>> &board) {
    if(board[empty_space.y][empty_space.x] == Tile::EMPTY) {
        return true;
    } else {
        return false;
    }
}


