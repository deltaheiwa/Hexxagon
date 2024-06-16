#ifndef HEXAGON_MOVE_H
#define HEXAGON_MOVE_H

#include "../main/util.h"
#include "playable_sides.h"

namespace Hexxagon {
    class Move {
    private:
        HexxagonUtil::Coordinate from;
        HexxagonUtil::Coordinate to;
        PlayableSides::Side side;

        int value = 0;
        bool is_copy = false;

    public:
        Move(HexxagonUtil::Coordinate* from, HexxagonUtil::Coordinate* to, PlayableSides::Side side, bool is_copy = false);
        Move(HexxagonUtil::Coordinate from, HexxagonUtil::Coordinate* to, PlayableSides::Side side, bool is_copy = false);
        Move(HexxagonUtil::Coordinate* from, HexxagonUtil::Coordinate to, PlayableSides::Side side, bool is_copy = false);
        Move(HexxagonUtil::Coordinate from, HexxagonUtil::Coordinate to, PlayableSides::Side side, bool is_copy = false);

        auto getFrom() const -> HexxagonUtil::Coordinate;

        auto getTo() const -> HexxagonUtil::Coordinate;

        auto getCoordinates() const -> std::pair<HexxagonUtil::Coordinate, HexxagonUtil::Coordinate>;

        auto getSide() const -> PlayableSides::Side;

        auto isCopy() const -> bool;

        auto toStr() const -> std::string;

        auto getValue() const -> int;

        auto operator-=(int const &value) const -> Move;

        auto operator+=(int const &value) const -> Move;

        auto operator==(Move const &move) const -> bool;

        auto operator!=(Move const &move) const -> bool;

        auto operator<(Move const &move) const -> bool;
    };

} // Hexxagon

#endif //HEXAGON_MOVE_H
