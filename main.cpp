#include <fmt/core.h>
#include "main/game.h"



auto main() -> int {
    auto game = Hexxagon::Game::getInstance();

    game->run();

    return 0;
}
