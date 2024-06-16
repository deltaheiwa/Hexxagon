#ifndef HEXAGON_PLAYER_H
#define HEXAGON_PLAYER_H

#include "playable_sides.h"

namespace Hexxagon {
    class Player : public PlayableSides {
    private:
        HexxagonUtil::Coordinate* selectedCoordinate = nullptr;
    public:
        Player();
        Player(Side alignment);
        ~Player() override = default;

        auto getType() const -> PlayerType override {
            return type;
        }

        auto setSelectedCoordinate(HexxagonUtil::Coordinate const &coordinate) -> void override;

        auto clearSelectedCoordinate() -> void override;

        auto getSelectedCoordinate() const -> HexxagonUtil::Coordinate* override;

        auto hasSelectedCoordinate() const -> bool override {
            return selectedCoordinate != nullptr;
        }
    };
}

#endif //HEXAGON_PLAYER_H
