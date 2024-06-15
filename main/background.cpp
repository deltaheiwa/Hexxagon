#include <thread>
#include "background.h"

#include "game_manager.h"
#include "util.h"

namespace Hexxagon {
    bool Background::isRunning = false;

    Background::Background() {}

    sf::CircleShape Background::structureShape() {
        sf::CircleShape particleShape;
        particleShape.setRadius(HexxagonUtil::generateRandomNumber(2.0f,6.0f));
        particleShape.setFillColor(sf::Color::White);
        return particleShape;
    }

    float Background::generateSpawnPos(float const &windowHeight) {
        return HexxagonUtil::generateRandomNumber(0.0f, windowHeight);
    }

    void Background::spawnParticle() {
        auto window = GameManager::getInstance()->getWindow();
        auto const [width, height] = window->getWindowDims();
        particles.push_back({structureShape(), {width, generateSpawnPos((float)height)}});
    }

    float Background::moveLeft(float &x, float const &radius) {
        x -= 8.0f / radius;
        return x;
    }

    void Background::drawParticles() {
        auto window = GameManager::getInstance()->getWindow();
        for (auto iteratorToParticle = particles.begin(); iteratorToParticle != particles.end();) {
            auto& [shape, pos] = *iteratorToParticle;
            auto& [x, y] = pos;
            if (x < 0) {
                iteratorToParticle = particles.erase(iteratorToParticle);
            } else {
                shape.setPosition(x, y);
                x = moveLeft(x, shape.getRadius());
                window->draw(shape);
                ++iteratorToParticle;
            }
        }
    }

    void Background::run() {
        isRunning = true;
        auto window = GameManager::getInstance()->getWindow();
        auto const [width, height] = window->getWindowDims();
        while (isRunning) {
            if (HexxagonUtil::generateRandomNumber(0, 100) < (std::size(particles) > 15 ? 2.0f : 4.0f)) {
                spawnParticle();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    void Background::powerOff() {
        isRunning = false;
    }

} // Hexxagon