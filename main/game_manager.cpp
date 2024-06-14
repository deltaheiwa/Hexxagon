#include "game_manager.h"
#include "../entities/player.h"
#include "../entities/ai.h"

#include "SFML/Graphics.hpp"

using namespace Hexxagon;

GameManager::GameManager() : window(sf::VideoMode(1600, 900), "Hexxagon", WindowWrapper::WINDOW_STATE::MENU), board(nullptr){
    window.setFramerateLimit(60);
}

GameManager* GameManager::getInstance() {
    static auto instance = new GameManager();
    return instance;
}

auto GameManager::getWindow() -> WindowWrapper& {
    return window;
}

auto GameManager::getBoard() -> Board& {
    return *board;
}

auto GameManager::createBoard(bool is_against_ai) -> void {
    std::shared_ptr<PlayableSides> player1 = std::make_shared<Player>(PlayableSides::RUBIES);
    std::shared_ptr<PlayableSides> player2;
    if (is_against_ai) player2 = std::make_shared<AI>(PlayableSides::PEARLS);
    else player2 = std::make_shared<Player>(PlayableSides::PEARLS);
    this->board = BoardBuilder()
            .setSize(4)
            .addPlayer(std::move(player1))
            .addPlayer(std::move(player2))
            .build();
    board->drawBoard(window);
}

auto GameManager::run() -> void {
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

auto GameManager::update() -> void {

}