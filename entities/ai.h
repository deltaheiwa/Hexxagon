#ifndef HEXAGON_AI_H
#define HEXAGON_AI_H

#include "playable_sides.h"

namespace Hexxagon {
    class AI : public PlayableSides {
    private:
    public:
        AI(Side side);
        ~AI() override = default;

        auto getType() const -> PlayerType override {
            return type;
        }

        auto setSelectedCoordinate(HexxagonUtil::Coordinate const &coordinate) -> void override { };

        auto clearSelectedCoordinate() -> void override { };

        auto getSelectedCoordinate() const -> HexxagonUtil::Coordinate* override { return nullptr; };

        auto hasSelectedCoordinate() const -> bool override { return false; };
    };
}

#endif //HEXAGON_AI_H
