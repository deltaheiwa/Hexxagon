#ifndef HEXAGON_BACKGROUND_H
#define HEXAGON_BACKGROUND_H

#include "SFML/Graphics.hpp"

namespace Hexxagon {

    class Background {
    private:
        sf::CircleShape shape;

        void structureShape();
    };

} // Hexxagon

#endif //HEXAGON_BACKGROUND_H
