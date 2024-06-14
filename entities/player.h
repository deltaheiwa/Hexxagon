#ifndef HEXAGON_PLAYER_H
#define HEXAGON_PLAYER_H

#include "playable_sides.h"

namespace Hexxagon {
    class Player : public PlayableSides {
    private:
        Side side;
    public:
        Player();
        Player(Side alignment);
        ~Player() override = default;

        auto getAlignment() const -> Side;
    };
}

#endif //HEXAGON_PLAYER_H
