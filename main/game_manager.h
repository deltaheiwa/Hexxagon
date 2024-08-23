#ifndef HEXAGON_GAME_MANAGER_H
#define HEXAGON_GAME_MANAGER_H

#include <queue>
#include <unordered_map>
#include "util.h"
#include "window_wrapper.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "../entities/board.h"
#include "fmt/chrono.h"

namespace Hexxagon {
    class GameManager;
}

class Hexxagon::GameManager final {
private:
    template<typename P>
    static std::unordered_map<std::string, const P> CONSTANTS;
public:
    auto operator=(const GameManager&) = delete;
    GameManager(GameManager &other_instance) = delete;
    ~GameManager() = delete;


    static GameManager* getInstance(const WindowWrapper::WindowResolutionConfig* window_res = nullptr);

    template<typename T>
    static auto addConstant(std::string const &constant_name, T constantVariable) -> void {
        CONSTANTS<T>.insert({constant_name, constantVariable});
    }

    template<typename T>
    static auto getConstant(std::string const &constant_name) -> const auto& {
        return CONSTANTS<T>[constant_name];
    }

    auto getWindow() -> std::shared_ptr<WindowWrapper>;
    auto getBoard() -> std::shared_ptr<Board>;
    auto createBoard() -> void;
    auto performMove(const Move* move) -> void;
    auto removeBoard() -> void;
    auto onGameScene() -> void;

    auto setLastMove(Move* move) -> void;
    auto getLastMove() -> Move*;
    auto clearLastMove() -> void;

    auto run() const -> void;

    auto saveGameToFile(std::string const &filename) -> void;
    auto loadGameFromFile(std::string const &filename) -> void;
private:
    GameManager();
    explicit GameManager(sf::VideoMode video_mode);
    explicit GameManager(sf::VideoMode video_mode, const WindowWrapper::WindowResolutionConfig& window_res);

    std::shared_ptr<WindowWrapper> window;
    std::shared_ptr<Board> board = nullptr;

    Move* last_move = nullptr;

    auto checkGameEnd() -> void;
};

template<typename P>
std::unordered_map<std::string, const P> Hexxagon::GameManager::CONSTANTS;

#endif //HEXAGON_GAME_MANAGER_H
