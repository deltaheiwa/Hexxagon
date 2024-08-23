#include <filesystem>
#include <fstream>

#include "game_manager.h"
#include "../entities/player.h"
#include "../entities/ai.h"

#include "fmt/core.h"

using namespace Hexxagon;


GameManager::GameManager() : window(std::make_shared<WindowWrapper>(sf::VideoMode(1600, 900), "Hexxagon", WindowWrapper::WINDOW_STATE::MENU, WindowWrapper::WindowResolutionConfig())), board(nullptr){
    window->setFramerateLimit(60);
}

GameManager::GameManager(sf::VideoMode video_mode) : window(std::make_shared<WindowWrapper>(video_mode, "Hexxagon", WindowWrapper::WINDOW_STATE::MENU, WindowWrapper::WindowResolutionConfig(video_mode.width, video_mode.height, false))), board(nullptr) {
    window->setFramerateLimit(60);
}

GameManager::GameManager(sf::VideoMode video_mode, const WindowWrapper::WindowResolutionConfig& window_res) : window(std::make_shared<WindowWrapper>(video_mode, "Hexxagon", WindowWrapper::WINDOW_STATE::MENU, window_res)), board(nullptr) {
    window->setFramerateLimit(60);
}

GameManager* GameManager::getInstance(const WindowWrapper::WindowResolutionConfig* window_res) {
    static auto instance = window_res == nullptr ? new GameManager() : new GameManager(sf::VideoMode(window_res->width, window_res->height), *window_res);
    return instance;
}

auto GameManager::getWindow() -> std::shared_ptr<WindowWrapper> {
    return window;
}

auto GameManager::getBoard() -> std::shared_ptr<Board> {
    return board;
}


auto GameManager::setLastMove(Move* move) -> void {
    last_move = move;
}

auto GameManager::getLastMove() -> Move* {
    return last_move;
}

auto GameManager::clearLastMove() -> void {
    last_move = nullptr;
}

auto GameManager::checkGameEnd() -> void {
    if (board->isNoEmptyTiles()) {
        fmt::print("Game ended\n");
    }
}

auto GameManager::removeBoard() -> void {
    board = nullptr;
}

auto GameManager::performMove(const Move* move) -> void {
    if (move == nullptr) {
        return;
    }
    auto playerOptional = board->getPlayer(board->getCurrentTurn());
    if (playerOptional == nullptr) {
        return;
    }
    auto player = playerOptional.value();

    board->addPawn(move->getTo(), move->getSide());
    if (!move->isCopy()) {
        board->removePawn(move->getFrom());
    }

    board->convertPawns(move->getTo(), move->getSide());

    player->clearSelectedCoordinate();

    checkGameEnd();
    board->switchTurn();
}

auto GameManager::run() const -> void {
    // General idea of a game loop.
    while (window->isOpen()) {
        window->processEvents();
        window->render();
    }

}

auto GameManager::onGameScene() -> void {
    if (board == nullptr && window->getState() == WindowWrapper::WINDOW_STATE::IN_GAME) {
        createBoard();
    }
}

auto GameManager::saveGameToFile(std::string const &filename) -> void {
    if (board == nullptr) {
        return;
    }
    auto boardFen = board->getFen();
    auto filePath = getConstant<std::filesystem::path>("HEXXAGON_PATH") / filename;
    fmt::print("Saving game to {}\n", filePath.string());
    std::ofstream file(filePath, std::ios::trunc);

    if (file.is_open()) {
        file << boardFen;
        file.close();
    }
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
    board->loadBoard({{-1, 0},{0, -1},{1, 1}});
    board->loadStartingPosition();
    board->drawBoard(*window);
}

auto GameManager::loadGameFromFile(std::string const &filename) -> void {
    auto filePath = getConstant<std::filesystem::path>("HEXXAGON_PATH") / filename;
    fmt::print("Loading game from {}\n", filePath.string());
    std::ifstream file(filePath);
    if (file.is_open()) {
        std::string fen;
        std::getline(file, fen);

        board = BoardBuilder()
                .setSize(4)
                .addPlayer(std::make_shared<Player>(PlayableSides::RUBIES))
                .addPlayer(std::make_shared<Player>(PlayableSides::PEARLS))
                .build();
        board->structureShapes();
        board->loadBoard({{-1, 0},{0, -1},{1, 1}});
        board->parseFen(fen);
        board->drawBoard(*window);

        file.close();
    }
}