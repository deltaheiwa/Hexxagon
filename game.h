#ifndef HEXAGON_GAME_H
#define HEXAGON_GAME_H

#include "SFML/Graphics/RenderWindow.hpp"

namespace Hexxagon {
    class Game;
}

class Hexxagon::Game final {
private:
    Game();
    ~Game() = default;
    sf::RenderWindow window;
    enum WINDOW_STATE {
        MENU,
        IN_GAME,
        PAUSED
    };
    WINDOW_STATE state;

    auto processEvents() -> void;
    auto update() -> void;
    auto render() -> void;

    auto setState(WINDOW_STATE state);
public:
    auto operator=(const Game&) = delete;
    Game(Game &other_instance) = delete;

    static Game& getInstance();

    auto run() -> void;
};

#endif //HEXAGON_GAME_H
