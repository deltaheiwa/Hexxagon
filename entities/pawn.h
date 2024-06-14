#ifndef HEXAGON_PAWN_H
#define HEXAGON_PAWN_H

#include "playable_sides.h"

namespace Hexxagon {
    class Pawn {
    public:
        Pawn();
        Pawn(PlayableSides::Side alignment);

        auto getAlignment() const -> PlayableSides::Side;
    private:
        PlayableSides::Side alignment;
        sf::CircleShape shape;
        static constexpr float radius = 20.0f;

        void structureShape();
    };
}

#endif //HEXAGON_PAWN_H
