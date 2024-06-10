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
        auto setSide(Side const &side) -> void;

        auto getAllPawnPositions() const -> std::set<HexxagonUtil::Coordinate>;

        auto addPawnPosition(HexxagonUtil::Coordinate const &position) -> void;
        auto removePawnPosition(HexxagonUtil::Coordinate const &position) -> void;


    private:
        Side side;
        std::set<HexxagonUtil::Coordinate> pawnPositions;
    };

} // Hexxagon

#endif //HEXAGON_PLAYABLE_SIDES_H
