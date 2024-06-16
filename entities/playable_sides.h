#ifndef HEXAGON_PLAYABLE_SIDES_H
#define HEXAGON_PLAYABLE_SIDES_H

#include <set>
#include <optional>
#include "../main/util.h"
#include "SFML/Graphics.hpp"

namespace Hexxagon {
    class PlayableSides {
    public:
        enum Side {
            RUBIES,
            PEARLS
        };

        enum PlayerType {
            HUMAN,
            AI
        };
    protected:
        PlayerType type;
        Side side;
        std::set<HexxagonUtil::Coordinate> occupiedCoordinates;

        PlayableSides(Side side, PlayerType type);
    public:
        auto getSide() -> PlayableSides::Side;

        virtual auto getType() const -> PlayerType = 0;

        auto getOccupiedCoordinates() const -> std::set<HexxagonUtil::Coordinate>;

        auto addOccupiedCoordinate(HexxagonUtil::Coordinate const &coordinate) -> void;

        auto removeOccupiedCoordinate(HexxagonUtil::Coordinate const &coordinate) -> void;

        virtual auto setSelectedCoordinate(HexxagonUtil::Coordinate const &coordinate) -> void = 0;

        virtual auto clearSelectedCoordinate() -> void = 0;

        virtual auto getSelectedCoordinate() const -> HexxagonUtil::Coordinate* = 0;

        virtual auto hasSelectedCoordinate() const -> bool = 0;


        virtual ~PlayableSides() = default;
    };

} // Hexxagon

#endif //HEXAGON_PLAYABLE_SIDES_H
