#include "playable_sides.h"
#include "ai.h"
#include "player.h"

namespace Hexxagon {
    auto PlayableSides::getSide() const -> Side {
        return side;
    }

    AI::AI(PlayableSides::Side side) : side(side) { }

    Player::Player() : side(PlayableSides::RUBIES) { }
    Player::Player(PlayableSides::Side alignment) : side(alignment) { }

} // Hexxagon