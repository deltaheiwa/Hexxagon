#ifndef HEXAGON_PLAYABLE_SIDES_H
#define HEXAGON_PLAYABLE_SIDES_H

#include <set>
#include "../main/util.h"
#include "SFML/Graphics.hpp"

namespace Hexxagon {
    class PlayableSides {
    public:
        enum Side {
            RUBIES,
            PEARLS
        };

        auto getSide() const -> Side;

        auto getOccupiedCoordinates() const -> std::set<HexxagonUtil::Coordinate>;

        auto addOccupiedCoordinate(HexxagonUtil::Coordinate const &coordinate) -> void;

        auto removeOccupiedCoordinate(HexxagonUtil::Coordinate const &coordinate) -> void;


        virtual ~PlayableSides() = default;


    private:
        Side side;
        std::set<HexxagonUtil::Coordinate> occupiedCoordinates;
    };

} // Hexxagon

#endif //HEXAGON_PLAYABLE_SIDES_H
