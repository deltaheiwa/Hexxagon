#ifndef HEXAGON_PLAYER_H
#define HEXAGON_PLAYER_H

#include "playable_sides.h"

namespace Hexxagon {
    class Player : public PlayableSides {
    private:
        Side side;
        HexxagonUtil::Coordinate* selectedCoordinate = nullptr;
    public:
        Player();
        Player(Side alignment);
        ~Player() override = default;

        auto getAlignment() const -> Side;

        auto setSelectedCoordinate(HexxagonUtil::Coordinate const &coordinate) -> void;

        auto clearSelectedCoordinate() -> void;

        auto getSelectedCoordinate() const -> HexxagonUtil::Coordinate*;

    };
}

#endif //HEXAGON_PLAYER_H
