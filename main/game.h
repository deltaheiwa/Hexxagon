#ifndef HEXAGON_GAME_H
#define HEXAGON_GAME_H

#include <queue>
#include "util.h"
#include "window_wrapper.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "../entities/board.h"

namespace Hexxagon {
    class Game;
}

class Hexxagon::Game final {
public:
    auto operator=(const Game&) = delete;
    Game(Game &other_instance) = delete;
    ~Game() = delete;

    static Game* getInstance();

    auto getWindow() -> WindowWrapper&;

    auto run() -> void;
private:
    Game();
    WindowWrapper window;

    std::string gameFenCode;
    std::queue<std::pair<HexxagonUtil::Coordinate, HexxagonUtil::Coordinate>> gamePgnMoves;

    auto update() -> void;
};

#endif //HEXAGON_GAME_H
