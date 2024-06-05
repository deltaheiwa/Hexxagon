#include "game.h"
#include <SFML/Graphics.hpp>

using namespace Hexxagon;

Game::Game() : window(sf::VideoMode(1600, 900), "Hexxagon"), state(WINDOW_STATE::MENU) {
    window.setFramerateLimit(24);
}

Game& Game::getInstance() {
    static Game instance = Game();
    return instance;
}

auto Game::run() -> void {
    // General idea of a game loop.
    while (window.isOpen()) {
        processEvents();
        update();

        // I don't think I *really* need to render on every frame
        // like I definitely could render only on button clicks && game events,
        // but it won't affect performance that much (after testing, refreshing black screen on 60 fps took ~20-30% of my GPU,
        // 9% of which being raw, and remainder was Windows system process,
        // which is... a bit more than I would expect from the black screen, but I assume it's just Windows having a stroke. On Linux it's not that bad)
        render();
    }
}

auto Game::setState(WINDOW_STATE windowState) {
    this->state=windowState;
}


auto Game::processEvents() -> void {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();
        else if (event.type == sf::Event::KeyPressed) {}
    }
}

auto Game::update() -> void {

}

auto Game::render() -> void {
    window.clear();

    switch (this->state) {
        case WINDOW_STATE::MENU:

        case WINDOW_STATE::IN_GAME:
            break;
        case WINDOW_STATE::PAUSED:
            break;
    }

    window.display();
}