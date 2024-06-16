#ifndef HEXAGON_WINDOW_WRAPPER_H
#define HEXAGON_WINDOW_WRAPPER_H

#include "SFML/Graphics.hpp"
#include "background.h"
#include <memory>
#include <thread>

namespace Hexxagon {
    class WindowWrapper;
}

class Hexxagon::WindowWrapper final : public sf::RenderWindow {
private:
    const std::string FONT_PATH = "../assets/pixelFont.ttf";
    unsigned int windowWidth = 0;
    unsigned int windowHeight = 0;
    float windowHeightPartition = 0;

    class MenuCache {
    public:
        enum MAIN_MENU_BUTTON {
            PLAY,
            LOAD,
            EXIT,
            CYCLE_BACK
        };

        enum START_SELECT_MENU_BUTTON {
            PLAYER_VS_PLAYER,
            PLAYER_VS_AI,
            BACK_START,
            CYCLE_BACK_START
        };

        enum LOAD_SELECT_MENU_BUTTON {
            LOAD_GAME,
            BACK_LOAD,
            CYCLE_BACK_LOAD
        };

        enum MENU_LAYER {
            MAIN,
            START_SELECT,
            LOAD_SELECT
        };
    private:
        static MAIN_MENU_BUTTON selectedMainMenuButton;
        static START_SELECT_MENU_BUTTON selectedStartSelectMenuButton;
        static LOAD_SELECT_MENU_BUTTON selectedLoadSelectMenuButton;
        static MENU_LAYER currentLayer;

        static int selectedSaveIndex;
    public:
        static auto getSelectedMainMenuButton() -> MAIN_MENU_BUTTON;
        static auto setSelectedMainMenuButton(MAIN_MENU_BUTTON const &button) -> void;

        static auto getSelectedStartSelectMenuButton() -> START_SELECT_MENU_BUTTON;
        static auto setSelectedStartSelectMenuButton(START_SELECT_MENU_BUTTON const &button) -> void;

        static auto getSelectedLoadSelectMenuButton() -> LOAD_SELECT_MENU_BUTTON;
        static auto setSelectedLoadSelectMenuButton(LOAD_SELECT_MENU_BUTTON const &button) -> void;

        static auto getCurrentLayer() -> MENU_LAYER;
        static auto setCurrentLayer(MENU_LAYER const &layer) -> void;

        static auto getSelectedSaveIndex() -> int;
        static auto addOneToSelectedSaveIndex() -> void;
        static auto subtractOneFromSelectedSaveIndex() -> void;

    };

    class PauseCache {
    public:
        enum PAUSE_BUTTON {
            RESUME,
            SAVE,
            MAIN_MENU,
            CYCLE_BACK_PAUSE
        };

        static PAUSE_BUTTON selectedPauseButton;
        static std::string saveFileName;

        static auto getSelectedPauseButton() -> PAUSE_BUTTON;
        static auto setSelectedPauseButton(PAUSE_BUTTON const &button) -> void;

        static auto getSaveFileName() -> std::string&;
    };

    class MenuEventHandler {
    public:
        static auto handleMainMenuKeyPressed(WindowWrapper* window, sf::Event::KeyEvent key) -> void;
        static auto handleStartSelectMenuKeyPressed(WindowWrapper* window, sf::Event::KeyEvent key) -> void;
        static auto handleLoadSelectMenuKeyPressed(WindowWrapper* window, sf::Event::KeyEvent key) -> void;
    };

    class GameEventHandler {
    public:
        static auto handleInGameKeyPressed(WindowWrapper* window, sf::Event::KeyEvent key) -> void;
        static auto handleInGameMousePressed(WindowWrapper* window, sf::Event::MouseButtonEvent mouse) -> void;
    };

    class PauseEventHandler {
    public:
        static auto handlePauseEvent(WindowWrapper* window, sf::Event event) -> void;
    };

    void loadIcon();

    sf::Font loadFont();

    void handleMenu();

    void determineMenuLayer(sf::Event event);

    bool isMouseOverButton(sf::Vector2i mousePosition, const sf::Text& button);

    void drawMainMenu(sf::Font &font);

    void drawStartSelectMenu(sf::Font &font);

    void drawLoadSelectMenu(sf::Font &font);

    void handleInGame();

    void handlePause();
public:
    enum WINDOW_STATE {
        MENU,
        IN_GAME,
        PAUSED
    };

    WINDOW_STATE state;

    Background background;
    std::unique_ptr<std::thread> backgroundThread;

    WindowWrapper(sf::VideoMode mode, const std::string& title, WINDOW_STATE windowState);
    typedef RenderWindow super;

    auto getState() const -> WINDOW_STATE;
    auto setState(WINDOW_STATE const &game_state);

    void cacheWindowSize(unsigned int width, unsigned int height);

    sf::Vector2i getMousePosition();

    float getWindowHeightPartition();

    std::pair<unsigned int, unsigned int> getWindowDims();

    void render();

    void processEvents();
};



#endif //HEXAGON_WINDOW_WRAPPER_H
