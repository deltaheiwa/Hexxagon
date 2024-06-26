#include <filesystem>
#include <fstream>
#include <iostream>

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

auto GameManager::setBufferedMove(Move* move) -> void {
    buffered_move = move;
}

auto GameManager::getBufferedMove() -> Move* {
    return buffered_move;
}

auto GameManager::clearBufferedMove() -> void {
    buffered_move = nullptr;
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

auto GameManager::performMove() -> void {
    if (buffered_move == nullptr) {
        return;
    }
    auto playerOptional = board->getPlayer(board->getCurrentTurn());
    if (playerOptional == nullptr) {
        return;
    }
    auto player = playerOptional.value();



    board->addPawn(buffered_move->getTo(), buffered_move->getSide());
    if (!buffered_move->isCopy()) {
        board->removePawn(buffered_move->getFrom());
    }

    board->convertPawns(buffered_move->getTo(), buffered_move->getSide());

    /*if (board->isNoEmptyTiles()) {
        fmt::print("No empty tiles\n");
    }*/

    board->switchTurn();
    // setLastMove(buffered_move);
    clearBufferedMove();
    player->clearSelectedCoordinate();
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
    performMove();
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