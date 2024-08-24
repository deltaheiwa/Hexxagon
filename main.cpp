#include <filesystem>
#include <fstream>

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

    std::shared_ptr<Hexxagon::WindowWrapper::WindowResolutionConfig> window_res_ptr = nullptr;

    Hexxagon::GameManager::addConstant("HEXXAGON_PATH", HEXXAGON);

    if (!exists(HEXXAGON)) {
        fmt::print("Creating directory {} \n", HEXXAGON.string());
        create_directory(HEXXAGON);

        sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

        Hexxagon::WindowWrapper::WindowResolutionConfig window_res(desktop.width, desktop.height, true);

        window_res.saveToFile();
        window_res_ptr = std::make_shared<Hexxagon::WindowWrapper::WindowResolutionConfig>(window_res);
    } else {
        auto window_res = Hexxagon::WindowWrapper::WindowResolutionConfig::loadFromFile();
        window_res_ptr = std::make_shared<Hexxagon::WindowWrapper::WindowResolutionConfig>(window_res);
    }

    auto const game = Hexxagon::GameManager::getInstance(window_res_ptr.get());

    game->run();

    return 0;
}
