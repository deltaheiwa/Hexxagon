#include "move.h"

namespace Hexxagon {
    Move::Move(HexxagonUtil::Coordinate* from, HexxagonUtil::Coordinate* to, PlayableSides::Side side, bool is_copy) : from(*from), to(*to), side(side), is_copy(is_copy) { }
    Move::Move(HexxagonUtil::Coordinate from, HexxagonUtil::Coordinate* to, PlayableSides::Side side, bool is_copy) : from(from), to(*to), side(side), is_copy(is_copy)  { }
    Move::Move(HexxagonUtil::Coordinate* from, HexxagonUtil::Coordinate to, PlayableSides::Side side, bool is_copy) : from(*from), to(to), side(side), is_copy(is_copy)  { }
    Move::Move(HexxagonUtil::Coordinate from, HexxagonUtil::Coordinate to, PlayableSides::Side side, bool is_copy) : from(from), to(to), side(side), is_copy(is_copy)  { }

    auto Move::getFrom() const -> HexxagonUtil::Coordinate {
        return from;
    }

    auto Move::getTo() const -> HexxagonUtil::Coordinate {
        return to;
    }

    auto Move::getCoordinates() const -> std::pair<HexxagonUtil::Coordinate, HexxagonUtil::Coordinate> {
        return std::make_pair(from, to);
    }

    auto Move::getSide() const -> PlayableSides::Side {
        return side;
    }

    auto Move::isCopy() const -> bool {
        return is_copy;
    }

    auto Move::toStr() const -> std::string {
        return (is_copy ? "Copy " : "Move ") + std::to_string(from.diagonal) + ", " + std::to_string(from.vertical) + " -> " + std::to_string(to.diagonal) + ", " + std::to_string(to.vertical) + " (" + std::to_string(value) + ")";
    }

    auto Move::getValue() const -> int {
        return value;
    }

    auto Move::operator-=(int const &value) const -> Move {
        Move move(from, to, side);
        move.value -= value;
        return move;
    }

    auto Move::operator+=(int const &value) const -> Move {
        Move move(from, to, side);
        move.value += value;
        return move;
    }

    auto Move::operator==(Move const &move) const -> bool {
        return from == move.from && to == move.to && side == move.side;
    }

    auto Move::operator!=(Move const &move) const -> bool {
        return from != move.from || to != move.to || side != move.side;
    }

    auto Move::operator<(Move const &move) const -> bool {
        return value < move.value;
    }
} // Hexxagon