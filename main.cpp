#include "main/game_manager.h"
#include "entities/playable_sides.h"


auto main() -> int {
    auto const game = Hexxagon::GameManager::getInstance();  // Pointer to the game instance

    game->run();



    return 0;
}
