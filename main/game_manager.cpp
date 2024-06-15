#include "game_manager.h"
#include "../entities/player.h"
#include "../entities/ai.h"

#include "SFML/Graphics.hpp"
#include "fmt/core.h"

using namespace Hexxagon;

GameManager::GameManager() : window(std::make_shared<WindowWrapper>(sf::VideoMode(1600, 900), "Hexxagon", WindowWrapper::WINDOW_STATE::MENU)), board(nullptr){
    window->setFramerateLimit(60);
}

GameManager* GameManager::getInstance() {
    static auto instance = new GameManager();
    return instance;
}

auto GameManager::getWindow() -> std::shared_ptr<WindowWrapper> {
    return window;
}

auto GameManager::getBoard() -> std::shared_ptr<Board> {
    return board;
}

auto GameManager::createBoard() -> void {
    if (board != nullptr) {
        return;
    }
    fmt::println("Creating board");
    std::shared_ptr<PlayableSides> player1 = std::make_shared<Player>(PlayableSides::RUBIES);
    std::shared_ptr<PlayableSides> player2;
    if (Board::getGameMode()) player2 = std::make_shared<AI>(PlayableSides::PEARLS);
    else player2 = std::make_shared<Player>(PlayableSides::PEARLS);
    this->board = BoardBuilder()
            .setSize(4)
            .addPlayer(std::move(player1))
            .addPlayer(std::move(player2))
            .build();
    board->structureShapes();
    board->loadBoard();
    board->loadStartingPosition();
    board->drawBoard(*window);
}

auto GameManager::run() -> void {
    // General idea of a game loop.
    while (window->isOpen()) {
        window->processEvents();
        update();
        window->render();
    }

}

auto GameManager::update() -> void {
    if (board == nullptr && window->getState() == WindowWrapper::WINDOW_STATE::IN_GAME) {
        createBoard();
    }


}