#ifndef HEXAGON_GAME_H
#define HEXAGON_GAME_H

#include "window_wrapper.h"
#include "SFML/Graphics/RenderWindow.hpp"

namespace Hexxagon {
    class Game;
}

class Hexxagon::Game final {
public:
    enum GAME_STATE {
        MENU,
        IN_GAME,
        PAUSED
    };

    auto operator=(const Game&) = delete;
    Game(Game &other_instance) = delete;

    static Game& getInstance();

    auto getState() const -> GAME_STATE;
    auto setState(GAME_STATE const &state);

    auto run() -> void;
private:
    Game();
    ~Game() = default;
    WindowWrapper window;
    GAME_STATE state;

    auto update() -> void;
};

#endif //HEXAGON_GAME_H
