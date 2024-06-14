#ifndef HEXAGON_AI_H
#define HEXAGON_AI_H

#include "playable_sides.h"

namespace Hexxagon {
    class AI : public PlayableSides {
    private:
        Side side;
    public:
        AI(Side side);
        ~AI() override = default;
    };
}

#endif //HEXAGON_AI_H
