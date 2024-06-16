#include <thread>
#include "window_wrapper.h"

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "fmt/core.h"
#include "../entities/board.h"
#include "game_manager.h"

using namespace Hexxagon;

WindowWrapper::MenuCache::MAIN_MENU_BUTTON WindowWrapper::MenuCache::selectedMainMenuButton;
WindowWrapper::MenuCache::START_SELECT_MENU_BUTTON WindowWrapper::MenuCache::selectedStartSelectMenuButton;
WindowWrapper::MenuCache::LOAD_SELECT_MENU_BUTTON WindowWrapper::MenuCache::selectedLoadSelectMenuButton;
WindowWrapper::MenuCache::MENU_LAYER WindowWrapper::MenuCache::currentLayer;

WindowWrapper::WindowWrapper(
        sf::VideoMode mode,
        const std::string& title,
        WINDOW_STATE windowState
        ) : super(mode, title, sf::Style::Titlebar | sf::Style::Close) // I didn't want to deal with resizing, so I just disabled it
        {
    state = windowState;
    background = Background();
    cacheWindowSize(mode.width, mode.height);
    loadIcon();
    backgroundThread = std::make_unique<std::thread>(&Hexxagon::Background::run, &background);
}

void WindowWrapper::loadIcon() {
    sf::Image icon;
    if (!icon.loadFromFile("../assets/icon.png")) {
        fmt::print("Failed to load icon from {}\n", "../assets/icon.png");
        icon.create(32, 32, sf::Color::White);
    }
    setIcon(32, 32, icon.getPixelsPtr());
}

sf::Font WindowWrapper::loadFont() {
    sf::Font font;
    if (!font.loadFromFile(FONT_PATH)) {
        fmt::print("Failed to load font from {}\n", FONT_PATH);
        exit(EXIT_FAILURE);
    }
    return font;
}

// ------------------ Menu cache ------------------

auto WindowWrapper::MenuCache::getSelectedMainMenuButton() -> MAIN_MENU_BUTTON {
    return selectedMainMenuButton;
};

auto WindowWrapper::MenuCache::setSelectedMainMenuButton(MAIN_MENU_BUTTON const &button) -> void {
    selectedMainMenuButton = button;
};

auto WindowWrapper::MenuCache::getSelectedStartSelectMenuButton() -> START_SELECT_MENU_BUTTON {
    return selectedStartSelectMenuButton;
};

auto WindowWrapper::MenuCache::setSelectedStartSelectMenuButton(START_SELECT_MENU_BUTTON const &button) -> void {
    selectedStartSelectMenuButton = button;
};

auto WindowWrapper::MenuCache::getSelectedLoadSelectMenuButton() -> LOAD_SELECT_MENU_BUTTON {
    return selectedLoadSelectMenuButton;
};

auto WindowWrapper::MenuCache::setSelectedLoadSelectMenuButton(LOAD_SELECT_MENU_BUTTON const &button) -> void {
    selectedLoadSelectMenuButton = button;
};

auto WindowWrapper::MenuCache::getCurrentLayer() -> MENU_LAYER {
    return currentLayer;
};

auto WindowWrapper::MenuCache::setCurrentLayer(MENU_LAYER const &layer) -> void {
    currentLayer = layer;
};

// ------------------ Menu cache ------------------

void WindowWrapper::cacheWindowSize(unsigned int width, unsigned int height) {
    windowWidth = width;
    windowHeight = height;
    windowHeightPartition = height / 18;
}

sf::Vector2i WindowWrapper::getMousePosition() {
    return sf::Mouse::getPosition(*this);
}

float WindowWrapper::getWindowHeightPartition() {
    return windowHeightPartition;
}

std::pair<unsigned int, unsigned int> WindowWrapper::getWindowDims() {
    return {windowWidth, windowHeight};
}

auto WindowWrapper::getState() const -> WINDOW_STATE {
    return state;
}

auto WindowWrapper::setState(WINDOW_STATE const &game_state) {
    state = game_state;
}


void WindowWrapper::render() {
    clear();
    background.drawParticles();

    switch (state) {
        case (WINDOW_STATE::MENU):
            handleMenu();
            break;
        case (WINDOW_STATE::IN_GAME):
            handleInGame();
            break;
        case (WINDOW_STATE::PAUSED):
            handlePause();
            break;
    }

    display();
}

// ------------------ Event handling ------------------

void WindowWrapper::determineMenuLayer(sf::Event event) {
    switch (MenuCache::getCurrentLayer()) {
        case MenuCache::MENU_LAYER::MAIN:
            MenuEventHandler::handleMainMenuKeyPressed(this, event.key);
            break;
        case MenuCache::MENU_LAYER::START_SELECT:
            MenuEventHandler::handleStartSelectMenuKeyPressed(this, event.key);
            break;
        case MenuCache::MENU_LAYER::LOAD_SELECT:
            MenuEventHandler::handleLoadSelectMenuKeyPressed(this, event.key);
            break;
    }
}

void WindowWrapper::MenuEventHandler::handleMainMenuKeyPressed(WindowWrapper* window, sf::Event::KeyEvent key) {
    if (key.code == sf::Keyboard::Enter) {
        switch (MenuCache::getSelectedMainMenuButton()) {
            case MenuCache::MAIN_MENU_BUTTON::PLAY:
                MenuCache::setCurrentLayer(MenuCache::MENU_LAYER::START_SELECT);
                MenuCache::setSelectedStartSelectMenuButton(MenuCache::START_SELECT_MENU_BUTTON::PLAYER_VS_PLAYER);
                break;
            case MenuCache::MAIN_MENU_BUTTON::LOAD:
                MenuCache::setCurrentLayer(MenuCache::MENU_LAYER::LOAD_SELECT);
                break;
            case MenuCache::MAIN_MENU_BUTTON::EXIT:
                window->close();
                break;
            case MenuCache::MAIN_MENU_BUTTON::CYCLE_BACK:
                break;
        }
    } else if (key.code == sf::Keyboard::Up || key.code == sf::Keyboard::Down) {
        short direction = key.code == sf::Keyboard::Up ? -1 : 1;
        MenuCache::setSelectedMainMenuButton(
                (MenuCache::MAIN_MENU_BUTTON)
                ((MenuCache::getSelectedMainMenuButton() + 1 * (direction)) % MenuCache::MAIN_MENU_BUTTON::CYCLE_BACK)
                );
    }
}

void WindowWrapper::MenuEventHandler::handleStartSelectMenuKeyPressed(WindowWrapper* window, sf::Event::KeyEvent key) {
    if (key.code == sf::Keyboard::Enter) {
        switch (MenuCache::getSelectedStartSelectMenuButton()) {
            case MenuCache::START_SELECT_MENU_BUTTON::PLAYER_VS_PLAYER:
                window->setState(WindowWrapper::WINDOW_STATE::IN_GAME);
                Board::setGameMode(false);
                break;
            case MenuCache::START_SELECT_MENU_BUTTON::PLAYER_VS_AI:
                window->setState(WindowWrapper::WINDOW_STATE::IN_GAME);
                Board::setGameMode(true);
                break;
            case MenuCache::START_SELECT_MENU_BUTTON::BACK_START:
                MenuCache::setCurrentLayer(MenuCache::MENU_LAYER::MAIN);
                break;
            case MenuCache::START_SELECT_MENU_BUTTON::CYCLE_BACK_START:
                break;
        }
    } else if (key.code == sf::Keyboard::Up || key.code == sf::Keyboard::Down) {
        short direction = key.code == sf::Keyboard::Up ? -1 : 1;
        MenuCache::setSelectedStartSelectMenuButton(
                (MenuCache::START_SELECT_MENU_BUTTON)
                ((MenuCache::getSelectedStartSelectMenuButton() + 1 * (direction)) % MenuCache::START_SELECT_MENU_BUTTON::CYCLE_BACK_START)
                );
    }
}

void WindowWrapper::MenuEventHandler::handleLoadSelectMenuKeyPressed(WindowWrapper* window, sf::Event::KeyEvent key) {
    if (key.code == sf::Keyboard::Enter) {
        switch (MenuCache::getSelectedLoadSelectMenuButton()) {
            case MenuCache::LOAD_SELECT_MENU_BUTTON::BACK_LOAD:
                MenuCache::setCurrentLayer(MenuCache::MENU_LAYER::MAIN);
                break;
            case MenuCache::LOAD_SELECT_MENU_BUTTON::CYCLE_BACK_LOAD:
                break;
        }
    } else if (key.code == sf::Keyboard::Up || key.code == sf::Keyboard::Down) {
        short direction = key.code == sf::Keyboard::Up ? -1 : 1;
        MenuCache::setSelectedLoadSelectMenuButton(
                (MenuCache::LOAD_SELECT_MENU_BUTTON)
                ((MenuCache::getSelectedLoadSelectMenuButton() + 1 * (direction)) % MenuCache::LOAD_SELECT_MENU_BUTTON::CYCLE_BACK_LOAD)
                );
    }
}

// ------

void WindowWrapper::GameEventHandler::handleInGameMousePressed(WindowWrapper* window, sf::Event::MouseButtonEvent mouse) {
    fmt::println("Mouse pressed at ({}, {})", mouse.x, mouse.y);
    auto board = GameManager::getInstance()->getBoard();
    auto pressedTiles = std::vector<HexxagonUtil::Coordinate>();
    for (auto &[coordinate, tile] : *board->getTiles()) {
        // fmt::println("Checking tile at ({}, {})", coordinate.vertical, coordinate.diagonal);
        auto tileShape = tile.getShape();
        auto bounds = tileShape->getGlobalBounds();
        // fmt::println("Bounds: left: {}, top: {}, width: {}, height: {}", bounds.left, bounds.top, bounds.width, bounds.height);
        if (bounds.contains(mouse.x, mouse.y)) {
            pressedTiles.push_back(coordinate);
        }
    }
    if (pressedTiles.size() > 1 || pressedTiles.empty()) {
        // Do nothing if more than one tile is pressed or no tile is pressed. For now.
        return;
    }

    auto pressedTile = pressedTiles[0];
    auto tile = board->getTile(pressedTile);
    if (!tile.has_value()) {
        fmt::println("Tile not found at ({}, {})", pressedTile.diagonal, pressedTile.vertical);
        return;
    }

    auto tileStatus = tile.value()->getStatus();
    fmt::println("Tile at ({}, {}) is {}", pressedTile.diagonal, pressedTile.vertical, tile.value()->getTileStatusString());

    auto playerOptional = board->getPlayer(board->getCurrentTurn());
    if (playerOptional == std::nullopt) {
        fmt::println("Player not found");
        return;
    }
    auto player = playerOptional.value();

    bool isHuman = player->getType() == PlayableSides::PlayerType::HUMAN;
    bool isCurrentTurn = board->getCurrentTurn() + 1 == *tileStatus;

    if (*tileStatus == Tile::TileStatus::EMPTY) {
        fmt::println("Tile is empty");
        if (player->hasSelectedCoordinate()) {
            auto selectedCoordinate = player->getSelectedCoordinate();
            auto oneStepAdjacentCoordinates = board->findAdjacentCoordinatesOneStep(*selectedCoordinate);
            auto twoStepAdjacentCoordinates = board->findAdjacentCoordinatesTwoSteps(*selectedCoordinate);
            bool isOneStep = std::find(
                    oneStepAdjacentCoordinates.begin(),
                    oneStepAdjacentCoordinates.end(),
                    pressedTile
                    ) != oneStepAdjacentCoordinates.end();
            bool isTwoSteps = std::find(
                    twoStepAdjacentCoordinates.begin(),
                    twoStepAdjacentCoordinates.end(),
                    pressedTile
                    ) != twoStepAdjacentCoordinates.end();

            if (!isOneStep && !isTwoSteps) {
                board->removeSelectedHighlights();
                player->clearSelectedCoordinate();
                return;
            }
            auto side = player->getSide();
            auto move = Move(selectedCoordinate, pressedTile, side, isOneStep);
            GameManager::getInstance()->setBufferedMove(&move);
        }
        return;
    }


    if (isCurrentTurn && isHuman) {
        fmt::println("Pressed tile is of the current turn");
        player->setSelectedCoordinate(pressedTile);
    }

}

void WindowWrapper::processEvents() {
    sf::Event event;
    while (pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                close();
                break;
            case sf::Event::KeyPressed:
                switch (state) {
                    case WINDOW_STATE::MENU:
                        determineMenuLayer(event);
                        break;
                    case WINDOW_STATE::IN_GAME:

                        break;
                    case WINDOW_STATE::PAUSED:
                        break;
                }
                break;
            case sf::Event::MouseButtonPressed:
                switch (state) {
                    case WINDOW_STATE::MENU:
                        break;
                    case WINDOW_STATE::IN_GAME:
                        GameEventHandler::handleInGameMousePressed(this, event.mouseButton);
                        break;
                    case WINDOW_STATE::PAUSED:
                        break;
                }
                break;
            default:
                break;
        }
    }
}

void WindowWrapper::handleMenu() {
    sf::Font font = loadFont();

    sf::Text titleText("Hexxagon", font, 100);
    titleText.setPosition((float)(windowWidth/2.5), (float)(windowHeight/windowHeightPartition));
    draw(titleText);


    switch (MenuCache::getCurrentLayer()) {
        case MenuCache::MENU_LAYER::MAIN:
            drawMainMenu(font);
            break;
        case MenuCache::MENU_LAYER::START_SELECT:
            drawStartSelectMenu(font);
            break;
        case MenuCache::MENU_LAYER::LOAD_SELECT:
            drawLoadSelectMenu(font);
            break;
    }
}

bool WindowWrapper::isMouseOverButton(sf::Vector2i mousePosition, const sf::Text& button) {
    auto bounds = button.getGlobalBounds();
    return bounds.contains(mousePosition.x, mousePosition.y);
}

void WindowWrapper::drawMainMenu(sf::Font &font) {
    static sf::Vector2f arrowPosition;

    sf::Text startText("Start game", font, 50);
    startText.setPosition((float)(windowWidth/4), (float)(windowHeight - windowHeightPartition*12));
    draw(startText);

    sf::Text loadText("Load game", font, 50);
    loadText.setPosition((float)(windowWidth/4), (float)(windowHeight - windowHeightPartition*11));
    draw(loadText);

    sf::Text exitText("Quit", font, 50);
    exitText.setPosition((float)(windowWidth/4), (float)(windowHeight - windowHeightPartition*10));
    draw(exitText);


    auto mousePosition = getMousePosition();

    if (isMouseOverButton(mousePosition, startText)) {
        MenuCache::setSelectedMainMenuButton(MenuCache::MAIN_MENU_BUTTON::PLAY);
    } else if (isMouseOverButton(mousePosition, loadText)) {
        MenuCache::setSelectedMainMenuButton(MenuCache::MAIN_MENU_BUTTON::LOAD);
    } else if (isMouseOverButton(mousePosition, exitText)) {
        MenuCache::setSelectedMainMenuButton(MenuCache::MAIN_MENU_BUTTON::EXIT);
    }

    sf::Vector2f startPos;
    sf::Vector2f loadPos;
    sf::Vector2f exitPos;

    switch (MenuCache::getSelectedMainMenuButton()) {
        case MenuCache::MAIN_MENU_BUTTON::PLAY:
            startPos = startText.getPosition();
            arrowPosition = {startPos.x - 50, startPos.y};
            break;
        case MenuCache::MAIN_MENU_BUTTON::LOAD:
            loadPos = loadText.getPosition();
            arrowPosition = {loadPos.x - 50, loadPos.y};
            break;
        case MenuCache::MAIN_MENU_BUTTON::EXIT:
            exitPos = exitText.getPosition();
            arrowPosition = {exitPos.x - 50, exitPos.y};
            break;
        default:
            break;
    }

    sf::Text selectArrow(">", font, 50);
    selectArrow.setPosition(arrowPosition.x, arrowPosition.y);
    if (arrowPosition != sf::Vector2f(0, 0)) draw(selectArrow);
}

void WindowWrapper::drawStartSelectMenu(sf::Font &font) {
    static sf::Vector2f arrowPosition;

    sf::Text hotSeatText("Hot seat", font, 50);
    hotSeatText.setPosition((float)(windowWidth/4), (float)(windowHeight - windowHeightPartition*12));
    draw(hotSeatText);

    sf::Text aiText("Computer", font, 50);
    aiText.setPosition((float)(windowWidth/4), (float)(windowHeight - windowHeightPartition*11));
    draw(aiText);

    sf::Text backText("Back", font, 50);
    backText.setPosition((float)(windowWidth/4), (float)(windowHeight - windowHeightPartition*10));
    draw(backText);

    auto mousePosition = getMousePosition();

    if (isMouseOverButton(mousePosition, hotSeatText)) {
        MenuCache::setSelectedStartSelectMenuButton(MenuCache::START_SELECT_MENU_BUTTON::PLAYER_VS_PLAYER);
    } else if (isMouseOverButton(mousePosition, aiText)) {
        MenuCache::setSelectedStartSelectMenuButton(MenuCache::START_SELECT_MENU_BUTTON::PLAYER_VS_AI);
    } else if (isMouseOverButton(mousePosition, backText)) {
        MenuCache::setSelectedStartSelectMenuButton(MenuCache::START_SELECT_MENU_BUTTON::BACK_START);
    }

    sf::Vector2f hotSeatPos;
    sf::Vector2f aiPos;
    sf::Vector2f backPos;

    switch (MenuCache::getSelectedStartSelectMenuButton()) {
        case MenuCache::START_SELECT_MENU_BUTTON::PLAYER_VS_PLAYER:
            hotSeatPos = hotSeatText.getPosition();
            arrowPosition = {hotSeatPos.x - 50, hotSeatPos.y};
            break;
        case MenuCache::START_SELECT_MENU_BUTTON::PLAYER_VS_AI:
            aiPos = aiText.getPosition();
            arrowPosition = {aiPos.x - 50, aiPos.y};
            break;
        case MenuCache::START_SELECT_MENU_BUTTON::BACK_START:
            backPos = backText.getPosition();
            arrowPosition = {backPos.x - 50, backPos.y};
            break;
        default:
            break;
    }

    sf::Text selectArrow(">", font, 50);
    selectArrow.setPosition(arrowPosition.x, arrowPosition.y);
    if (arrowPosition != sf::Vector2f(0, 0)) draw(selectArrow);
};

void WindowWrapper::drawLoadSelectMenu(sf::Font &font) {
    static sf::Vector2f arrowPosition;
    // TODO: Implement load select menu
    sf::Text backText("Back", font, 50);
}

void WindowWrapper::handleInGame() {
    GameManager::getInstance()->getBoard()->drawBoard(*this);
}

void WindowWrapper::handlePause() {

}
