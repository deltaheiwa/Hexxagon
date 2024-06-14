#ifndef HEXAGON_PLAYABLE_SIDES_H
#define HEXAGON_PLAYABLE_SIDES_H

#include <set>
#include "../main/util.h"

namespace Hexxagon {
    class PlayableSides {
    public:
        enum Side {
            RUBIES,
            PEARLS
        };

        auto getSide() const -> Side;

        virtual ~PlayableSides() = default;

    private:
        Side side;
        std::set<HexxagonUtil::Coordinate> occupiedCoordinates;
    };

} // Hexxagon

#endif //HEXAGON_PLAYABLE_SIDES_H
