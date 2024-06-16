#include <filesystem>

#include "main/game_manager.h"
#include "fmt/core.h"

auto main() -> int {
    using namespace std::filesystem;

#if _WIN32 || _WIN64
    fmt::print("Windows detected\n");
    path const APPDATA = getenv("APPDATA");
    path const HEXXAGON = APPDATA / "Hexxagon";
#elif __linux__ || __APPLE__
    fmt::print("Linux or MacOS detected\n");
    path const HOME = getenv("HOME");
    path const HEXXAGON = HOME / ".hexxagon";
#endif

    if (!exists(HEXXAGON)) {
        fmt::print("Creating directory {} \n", HEXXAGON.string());
        create_directory(HEXXAGON);
    }

    auto const game = Hexxagon::GameManager::getInstance();  // Pointer to the game instance

    Hexxagon::GameManager::addConstant("HEXXAGON_PATH", HEXXAGON);

    game->run();

    return 0;
}
