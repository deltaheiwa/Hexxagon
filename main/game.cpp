#include "game.h"
#include "SFML/Graphics.hpp"

using namespace Hexxagon;

Game::Game() : window(sf::VideoMode(1600, 900), "Hexxagon", WindowWrapper::WINDOW_STATE::MENU) {
    window.setFramerateLimit(60);
}

Game* Game::getInstance() {
    static auto instance = new Game();
    return instance;
}

auto Game::getWindow() -> WindowWrapper& {
    return window;
}

auto Game::run() -> void {
    // General idea of a game loop.
    while (window.isOpen()) {
        window.processEvents();
        update();

        // I don't think I *really* need to render on every frame
        // like I definitely could render only on button clicks && game events,
        // but it won't affect performance that much (after testing, refreshing black screen on 60 fps took ~20-30% of my GPU,
        // 9% of which being raw, and remainder was Windows system process,
        // which is... a bit more than I would expect from the black screen, but I assume it's just Windows having a stroke. On Linux it's not that bad)
        window.render();
    }
}

auto Game::update() -> void {

}