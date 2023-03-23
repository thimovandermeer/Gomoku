//
// Created by Thimo Van der meer on 16/03/2023.
//

#include "CommonValidationCode.hpp"
#include "logger.hpp"
#include <vector>

BoundaryCheckReturn check_right_boundary(Coordinate boundaryCoords, Coordinate newCoords, Direction direction,
                                         const std::vector<std::vector<Tile>>& board) {
    LOG("boundary_coords in right boundary checking %i %i", boundaryCoords.y, boundaryCoords.x);
    LOG("Wat is de DIR %i", direction);
    BoundaryCheckReturn result{};
    if (direction == HORIZONTAL) {
        auto threeType = check_right_boundary_horizontal(boundaryCoords, newCoords, board);
        result.doubleType = threeType;
        result.openSpace = Coordinate{-1, -1};
        if (threeType == EMPTYSPACE) {
            auto openSpaceCoords = newCoords;
            openSpaceCoords.x = newCoords.x - 1;
            result.openSpace = openSpaceCoords;
            result.doubleType = threeType;
        }
        LOG("IK RETURN HORIZONTAL");
        return result;
    } else if (direction == VERTICAL) {
        auto threeType = check_right_boundary_vertical(boundaryCoords, newCoords, board);
        LOG("THREE TYPE = %i", threeType);
        result.doubleType = threeType;
        result.openSpace = Coordinate{-1, -1};
        if (threeType == EMPTYSPACE) {
            auto openSpaceCoords = newCoords;
            openSpaceCoords.y = newCoords.y - 1;
            result.openSpace = openSpaceCoords;
            result.doubleType = threeType;
        }
        LOG("WAT RETURN IK UBERHAUPT %i", result);
        LOG("IK RETURN VERTICAL");
        return result;
    } else if (direction == CROSS) {
        auto threeType = check_right_boundary_cross(boundaryCoords, newCoords, board);
        result.doubleType = threeType;
        result.openSpace = Coordinate{-1, -1};
        if (threeType == EMPTYSPACE) {
            auto openSpaceCoords = newCoords;
            openSpaceCoords.y = newCoords.y - 1;
            openSpaceCoords.x = newCoords.x - 1;
            result.openSpace = openSpaceCoords;
            result.doubleType = threeType;
            return result;
        }
        LOG("IK RETURN CROSS");
        return result;
    }
    result.doubleType = NONE;
    result.openSpace = Coordinate{-1, -1};
    LOG("Did not access any right boundary direction checks");
    return result;
}

DoubleType check_right_boundary_horizontal(Coordinate boundaryCoords, Coordinate newCoords,
                                           const std::vector<std::vector<Tile>>& board) {
    if (newCoords.y == boundaryCoords.y) {
        LOG("We are on the same horizontal axis");
        if (newCoords.x - boundaryCoords.x == 1) {
            LOG("Matching new[%i] boundary[%i]", newCoords.x, boundaryCoords.x);
            return NORMAL;
        }
        if (newCoords.x - boundaryCoords.x == 2) {
            LOG("Potentially one empty space in between");
            auto openSpaceCoords = newCoords;
            openSpaceCoords.x = newCoords.x - 1;
            LOG("OPEN space coords = %i", openSpaceCoords.x);
            if (open_space_is_empty(openSpaceCoords, board)) {
                LOG("Match horizontal we create double three with empty space in the middle new[%i] boundary[%i]",
                    newCoords.x, newCoords.y);
                return EMPTYSPACE;
            } else {
                LOG("The space in between was not empty");
                return NONE;
            }
        }
        LOG("We are on the same horizontal axis but not in line new[%i] boundary[%i]", newCoords.x, boundaryCoords.x);
        return NONE;
    }
    return NONE;
}

DoubleType check_right_boundary_vertical(Coordinate boundaryCoords, Coordinate newCoords,
                                         const std::vector<std::vector<Tile>>& board) {
    if (newCoords.x == boundaryCoords.x) {
        LOG("We are on the same vertical axis");
        if (newCoords.y - boundaryCoords.y == 1) {
            LOG("Matching new[%i] boundary[%i]", newCoords.y, boundaryCoords.y);
            return NORMAL;
        }
        if (newCoords.y - boundaryCoords.y == 2) {
            LOG("new coords y = %i boundary coords y", newCoords.y, boundaryCoords.y);
            auto openSpaceCoords = newCoords;
            openSpaceCoords.y = newCoords.y - 1;
            LOG("OPEN space coords = %i", openSpaceCoords.x);
            if (open_space_is_empty(openSpaceCoords, board)) {
                LOG("Match horizontal we create double three with empty space in the middle new[%i] boundary[%i]",
                    newCoords.x, newCoords.y);
                return EMPTYSPACE;
            } else {
                LOG("The space in between was not empty");
                return NONE;
            }
        }
        LOG("We are on the same vertical axis but not in line new[%i] boundary[%i]", newCoords.y, boundaryCoords.y);
        return NONE;
    }
    LOG("ERROR FOUND");
    return NONE;
}

DoubleType check_right_boundary_cross(Coordinate boundaryCoords, Coordinate newCoords,
                                      const std::vector<std::vector<Tile>>& board) {
    if ((newCoords.y - boundaryCoords.y) == 1) {
        if (newCoords.x - boundaryCoords.x == 1) {
                boundaryCoords.x);
            return NORMAL;
        }
            boundaryCoords.x);
        return NONE;
    } else if ((newCoords.y - boundaryCoords.y) == 2) {
        auto openSpaceCoords = newCoords;
        openSpaceCoords.y = newCoords.y - 1;
        openSpaceCoords.x = newCoords.x - 1;
        if (open_space_is_empty(openSpaceCoords, board)) {
            return EMPTYSPACE;
        } else {
            return NONE;
        }
    }
    return NONE;
}

DoubleType check_left_boundary_horizontal(Coordinate boundaryCoords,
                                          Coordinate newCoords, const std::vector<std::vector<Tile>>& board) {
    if (newCoords.y == boundaryCoords.y) {
        if (newCoords.x - boundaryCoords.x == -1) {
            return NORMAL;
        }
        if (newCoords.x - boundaryCoords.x == -2) {
            auto openSpaceCoords = newCoords;
            openSpaceCoords.x = newCoords.x + 1;
            if (open_space_is_empty(openSpaceCoords, board)) {
                return EMPTYSPACE;
            } else {
                return NONE;
            }
        }
        return NONE;
    }
    return NONE;
}

DoubleType check_left_boundary_vertical(Coordinate boundaryCoords, Coordinate newCoords,
                                        const std::vector<std::vector<Tile>>& board) {
    if (newCoords.x == boundaryCoords.x) {
        if (newCoords.y - boundaryCoords.y == -1) {
            return NORMAL;
        }
        if (newCoords.y - boundaryCoords.y == -2) {
            auto openSpaceCoords = newCoords;
            openSpaceCoords.y = newCoords.y + 1;
            if (open_space_is_empty(openSpaceCoords, board)) {
                return EMPTYSPACE;
            } else {
                return NONE;
            }
        }
        return NONE;
    }
    return NONE;
}

DoubleType check_left_boundary_cross(Coordinate boundaryCoords, Coordinate newCoords,
                                     const std::vector<std::vector<Tile>>& board) {
    if ((newCoords.y - boundaryCoords.y) == -1) {
        if (newCoords.x - boundaryCoords.x == -1) {
            return NORMAL;
        }
        return NONE;
    } else if ((newCoords.y - boundaryCoords.y) == -2) {
        auto openSpaceCoords = newCoords;
        openSpaceCoords.y = newCoords.y + 1;
        openSpaceCoords.x = newCoords.x + 1;
        if (open_space_is_empty(openSpaceCoords, board)) {
            return EMPTYSPACE;
        } else {
            return NONE;
        }
    }
    return NONE;
}


BoundaryCheckReturn check_left_boundary(Coordinate boundaryCoords, Coordinate newCoords, Direction direction,
                                        const std::vector<std::vector<Tile>>& board) {
    BoundaryCheckReturn result{};
    if (direction == HORIZONTAL) {
        auto threeType = check_left_boundary_horizontal(boundaryCoords, newCoords, board);
        result.doubleType = threeType;
        result.openSpace = Coordinate{-1, -1};
        if (threeType == EMPTYSPACE) {
            auto openSpaceCoords = newCoords;
            openSpaceCoords.x = newCoords.x + 1;
            result.openSpace = openSpaceCoords;
            result.doubleType = threeType;
        }
        return result;
    } else if (direction == VERTICAL) {
        auto threeType = check_left_boundary_vertical(boundaryCoords, newCoords, board);
        result.doubleType = threeType;
        result.openSpace = Coordinate{-1, -1};
        if (threeType == EMPTYSPACE) {
            auto openSpaceCoords = newCoords;
            openSpaceCoords.y = newCoords.y + 1;
            result.openSpace = openSpaceCoords;
            result.doubleType = threeType;
        }
        return result;
    } else if (direction == CROSS) {
        auto threeType = check_left_boundary_cross(boundaryCoords, newCoords, board);
        result.doubleType = threeType;
        result.openSpace = Coordinate{-1, -1};
        if (threeType == EMPTYSPACE) {
            auto openSpaceCoords = newCoords;
            openSpaceCoords.y = newCoords.y + 1;
            openSpaceCoords.x = newCoords.x + 1;
            result.openSpace = openSpaceCoords;
            result.doubleType = threeType;
        }
        return result;
    }
    result.doubleType = NONE;
    result.openSpace = Coordinate{-1, -1};
    return result;
}

bool check_free_left(Coordinate leftBoundary, Direction dir, const std::vector<std::vector<Tile>>& board) {
    if (dir == HORIZONTAL) {
        if (board[leftBoundary.y][leftBoundary.x - 1] == Tile::EMPTY) {
            return true;
        } else {
            return false;
        }
    }
    if (dir == VERTICAL) {
        if (board[leftBoundary.y - 1][leftBoundary.x] == Tile::EMPTY) {
            return true;
        } else {
            return false;
        }
    }
    if (dir == CROSS) {
        if (board[leftBoundary.y - 1][leftBoundary.x - 1] == Tile::EMPTY) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}

bool check_free_right(Coordinate rightBoundary, Direction dir, const std::vector<std::vector<Tile>>& board) {
    if (dir == HORIZONTAL) {
        if (board[rightBoundary.y][rightBoundary.x + 1] == Tile::EMPTY) {
            return true;
        } else {
            return false;
        }
    }
    if (dir == VERTICAL) {
        if (board[rightBoundary.y + 1][rightBoundary.x] == Tile::EMPTY) {
            return true;
        } else {
            return false;
        }
    }
    if (dir == CROSS) {
        if (board[rightBoundary.y + 1][rightBoundary.x + 1] == Tile::EMPTY) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}

bool open_space_is_empty(Coordinate emptySpace, const std::vector<std::vector<Tile>>& board) {
    if (board[emptySpace.y][emptySpace.x] == Tile::EMPTY) {
        return true;
    } else {
        return false;
    }
}


