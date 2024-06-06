#ifndef HEXAGON_WINDOW_WRAPPER_H
#define HEXAGON_WINDOW_WRAPPER_H

#include <SFML/Graphics.hpp>

namespace Hexxagon {
    class WindowWrapper;
}

class Hexxagon::WindowWrapper : public sf::RenderWindow {
public:
    typedef RenderWindow super;
    WindowWrapper(sf::VideoMode, const std::string&);

    void render();

    void processEvents();

    void handleMenu();

    void handleInGame();

    void handlePause();
};


#endif //HEXAGON_WINDOW_WRAPPER_H
