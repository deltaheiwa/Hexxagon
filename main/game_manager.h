#ifndef HEXAGON_GAME_MANAGER_H
#define HEXAGON_GAME_MANAGER_H

#include <queue>
#include "util.h"
#include "window_wrapper.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "../entities/board.h"

namespace Hexxagon {
    class GameManager;
}

class Hexxagon::GameManager final {
public:
    auto operator=(const GameManager&) = delete;
    GameManager(GameManager &other_instance) = delete;
    ~GameManager() = delete;

    static GameManager* getInstance();

    auto getWindow() -> std::shared_ptr<WindowWrapper>;
    auto getBoard() -> std::shared_ptr<Board>;
    auto createBoard() -> void;

    auto run() -> void;
private:
    GameManager();
    std::shared_ptr<WindowWrapper> window;
    std::shared_ptr<Board> board = nullptr;

    std::string gameFenCode;
    std::queue<std::pair<HexxagonUtil::Coordinate, HexxagonUtil::Coordinate>> gamePgnMoves;

    auto update() -> void;
};

#endif //HEXAGON_GAME_MANAGER_H
