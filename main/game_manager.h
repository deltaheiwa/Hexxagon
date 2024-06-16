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
    auto performMove() -> void;

    auto setBufferedMove(Move* move) -> void;
    auto getBufferedMove() -> Move*;
    auto clearBufferedMove() -> void;

    auto setLastMove(Move* move) -> void;
    auto getLastMove() -> Move*;
    auto clearLastMove() -> void;

    auto run() -> void;
private:
    GameManager();
    std::shared_ptr<WindowWrapper> window;
    std::shared_ptr<Board> board = nullptr;

    Move* last_move = nullptr;

    Move* buffered_move = nullptr;

    auto update() -> void;
};

#endif //HEXAGON_GAME_MANAGER_H
