#ifndef HEXAGON_BACKGROUND_H
#define HEXAGON_BACKGROUND_H

#include <deque>
#include "SFML/Graphics.hpp"

namespace Hexxagon {

    class Background {
    private:
        static bool isRunning;

        std::vector<std::pair<sf::CircleShape, std::pair<float, float>>> particles;

        sf::CircleShape structureShape();
        float generateSpawnPos(float const &windowHeight);
        void spawnParticle();
        float moveLeft(float &x, float const &radius);
    public:
        Background();

        void run();
        void drawParticles();

        static void powerOff();
    };

} // Hexxagon

#endif //HEXAGON_BACKGROUND_H
