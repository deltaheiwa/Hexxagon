#include "playable_sides.h"

namespace Hexxagon {
    auto PlayableSides::getSide() const -> Side {
        return side;
    }

    auto PlayableSides::setSide(Side const &setting_side) -> void {
        this->side = setting_side;
    }

    auto PlayableSides::getAllPawnPositions() const -> std::set<HexxagonUtil::Coordinate> {
        return pawnPositions;
    }

    auto PlayableSides::addPawnPosition(HexxagonUtil::Coordinate const &position) -> void {
        pawnPositions.insert(position);
    }

    auto PlayableSides::removePawnPosition(HexxagonUtil::Coordinate const &position) -> void {
        pawnPositions.erase(position);
    }
} // Hexxagon