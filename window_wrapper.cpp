#include "window_wrapper.h"

#include "game.h"
#include <fmt/core.h>

using namespace Hexxagon;

WindowWrapper::WindowWrapper(sf::VideoMode mode, const std::string& title) : super(mode, title) {

}

void WindowWrapper::render() {
    clear();

    switch (Game::getInstance().getState()) {
        case (Game::MENU):
            // fmt::println("Menu");
            break;
        case (Game::IN_GAME):
            // fmt::println("In game");
            break;
        case (Game::PAUSED):
            // fmt::println("Paused");
            break;
    }

    display();
}

void WindowWrapper::processEvents() {
    sf::Event event;
    while (pollEvent(event)) {
        if (event.type == sf::Event::Closed) close();
        else if (event.type == sf::Event::KeyPressed) {}
        else if (event.type == sf::Event::MouseButtonPressed) {}
    }
}

