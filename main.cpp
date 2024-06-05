#include <iostream>
#include <SFML/Graphics.hpp>
#include <fmt/core.h>
#include "game.h"



auto main() -> int {
    auto& game = Hexxagon::Game::getInstance();

    game.run();

    return 0;
}
