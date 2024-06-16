#include <optional>
#include <cmath>
#include <algorithm>
#include <utility>
#include "board.h"
#include "tile.h"
#include "ai.h"
#include "../main/window_wrapper.h"
#include "../main/game_manager.h"
#include "fmt/core.h"
#include "player.h"

namespace Hexxagon {
    bool Board::is_against_ai = false;
    std::string Board::starting_position = "r3p/6/7/8/p7r/8/7/6/r3p r";

    auto Board::getSize() const -> short {
        return size;
    }

    auto Board::getTile(HexxagonUtil::Coordinate const &coordinate) const -> std::optional<Tile*> {
        // https://en.cppreference.com/w/cpp/utility/optional
        if (!tiles.contains(coordinate)) {
            return std::nullopt;
        }
        return const_cast<Tile*>(&tiles.at(coordinate));
    }

    auto Board::setTile(const HexxagonUtil::Coordinate &coordinate, Tile tile) -> Tile* {
        tiles[coordinate] = std::move(tile);
        return &tiles.at(coordinate);
    }

    auto Board::getTiles() -> std::map<HexxagonUtil::Coordinate, Tile>* {
        return &tiles;
    }

    auto Board::getGameMode() -> bool {
        return Board::is_against_ai;
    }

    auto Board::setGameMode(bool againstAi) -> void {
        Board::is_against_ai = againstAi;
    }

    auto Board::getCurrentTurn() -> PlayableSides::Side {
        return current_turn;
    }

    void Board::switchTurn() {
        current_turn = current_turn == PlayableSides::Side::RUBIES ? PlayableSides::Side::PEARLS : PlayableSides::Side::RUBIES;
    }

    auto Board::getPlayer(PlayableSides::Side side) -> std::optional<std::shared_ptr<PlayableSides>> {
        for (auto player : players) {
            auto playerSide = player->getSide();
            if (playerSide == side) {
                return player;
            }
        }
        return std::nullopt;
    }

    auto Board::addPawn(HexxagonUtil::Coordinate const &coordinate, PlayableSides::Side side) -> void {
        auto tile = getTile(coordinate);
        if (tile.has_value()) {
            tile.value()->setStatus(side == PlayableSides::Side::RUBIES ? Tile::RUBY : Tile::PEARL);
            players[side == PlayableSides::Side::RUBIES ? 0 : 1]->addOccupiedCoordinate(coordinate);
        }
    }

    auto Board::convertPawns(HexxagonUtil::Coordinate const &coordinate, PlayableSides::Side side) -> void {
        auto adjacentCoordinates = findAdjacentCoordinatesOneStep(coordinate);
        for (auto adjacentCoordinate : adjacentCoordinates) {
            auto tile = getTile(adjacentCoordinate);
            if (tile.has_value()) {
                auto tileStatus = *tile.value()->getStatus();
                if (tileStatus == Tile::EMPTY) {
                    continue;
                }
                if (tileStatus == (side == PlayableSides::Side::RUBIES ? Tile::PEARL : Tile::RUBY)) {
                    tile.value()->setStatus(side == PlayableSides::Side::RUBIES ? Tile::RUBY : Tile::PEARL);
                }
            }
        }
    }

    auto Board::removePawn(HexxagonUtil::Coordinate const &coordinate) -> void {
        auto tile = getTile(coordinate);
        if (tile.has_value()) {
            tile.value()->setStatus(Tile::EMPTY);
            players[0]->removeOccupiedCoordinate(coordinate);
            players[1]->removeOccupiedCoordinate(coordinate);
        }
    }

    auto Board::parseFen(std::string const &fen) -> void {
        auto gameInfo = HexxagonUtil::splitString(fen, ' ');
        auto currentTurn = gameInfo[1];
        auto columns = HexxagonUtil::splitString(gameInfo[0], '/');
        auto player1 = players[0];
        auto player2 = players[1];

        for (int columnIndex = 0; columnIndex < columns.size(); columnIndex++) {
            auto x = (columnIndex <= columns.size()/2) ? -size : -(2*size)+columnIndex;
            auto y = columnIndex - size;
            for (char c : columns[columnIndex]) {
                fmt::println("Processing character: {}. Coordinates: {}, {}", c, x, y);
                if (std::isdigit(c)) {
                    x += (int)(c - '0');
                fmt::println("Skipping {} spaces", c);
                } else if (c == 'r' || c == 'p') {
                    auto tile = getTile({x, y});
                    if (tile.has_value()) {
                        tile.value()->setStatus(c == 'r' ? Tile::RUBY : Tile::PEARL);
                        c == 'r' ? player1->addOccupiedCoordinate({x, y}) : player2->addOccupiedCoordinate({x, y});
                    }
                    fmt::println("Setting tile at ({}, {}) to {}", x, y, c == 'r' ? "RUBY" : "PEARL");
                    x++;
                } else {
                    fmt::println("Invalid character in FEN: {}", c);
                }
            }
        }
        current_turn = currentTurn == "r" ? PlayableSides::Side::RUBIES : PlayableSides::Side::PEARLS;
    }

    auto Board::getFen() -> std::string {
        std::string fen;
        for (int vert = -size; vert <= size; vert++) {
            int diagStart = (vert <= 0) ? -size : -size + vert;
            int diagEnd = (vert > 0) ? size : size - vert;
            int emptyCount = 0;
            for (int diag = diagStart; diag <= diagEnd; diag++) {
                auto tile = getTile({diag, vert});
                if (tile.has_value()) {
                    auto tileStatus = *tile.value()->getStatus();
                    if (tileStatus == Tile::EMPTY) {
                        emptyCount++;
                    } else {
                        if (emptyCount > 0) {
                            fen += std::to_string(emptyCount);
                            emptyCount = 0;
                        }
                        fen += tileStatus == Tile::RUBY ? "r" : "p";
                    }
                } else if (std::find(excludedCoordinates.begin(), excludedCoordinates.end(), HexxagonUtil::Coordinate(diag, vert)) != excludedCoordinates.end()) {
                    emptyCount++;
                }
            }
            if (emptyCount > 0) {
                fen += std::to_string(emptyCount);
            }
            if (vert != size) {
                fen += "/";
            }
        }
        fen += " ";
        fen += current_turn == PlayableSides::Side::RUBIES ? "r" : "p";
        return fen;
    }

    auto Board::loadStartingPosition() -> void {
        parseFen(starting_position);
    }
    void Board::structureShapes() {
        // Ruby shape
        rubyShape.setFillColor(sf::Color::Red);
        rubyShape.setOutlineThickness(4);
        rubyShape.setOutlineColor(HexxagonUtil::CustomColors::DarkRed);
        rubyShape.setPointCount(6);
        rubyShape.setRadius(pawnRadius);
        rubyShape.setRotation(90);
        rubyShape.setOrigin(pawnRadius, pawnRadius);

        // Pearl shape
        pearlShape.setFillColor(HexxagonUtil::CustomColors::SoftLightBlue);
        pearlShape.setOutlineThickness(3);
        pearlShape.setOutlineColor(HexxagonUtil::CustomColors::SoftPink);
        pearlShape.setRadius(pawnRadius);
        pearlShape.setOrigin(pawnRadius, pawnRadius);
    }


    sf::CircleShape Board::getPawnShape(PlayableSides::Side const &side) {
        return side == PlayableSides::Side::RUBIES ? rubyShape : pearlShape;
    }

    auto Board::loadBoard(std::vector<HexxagonUtil::Coordinate> const &excluded = {}) -> void {
        auto const ex_tile = Tile({0,0});

        auto const hexWidth = 2 * ex_tile.getRadius();
        auto const hexHeight = std::sqrt(3) * ex_tile.getRadius();

        auto window = GameManager::getInstance()->getWindow();

        auto const [width, height] = window->getWindowDims();

        auto rows = size;

        excludedCoordinates = excluded; // holes in the middle of the board

        auto const offsetX = width / 2 - (hexWidth * rows) / 2;
        auto const offsetY = window->getWindowHeightPartition() * 2;
        // size = 4;
        for (int q = -size; q <= size; q++) {
            for (int r = 0; r <= rows; r++) {
                auto const flipper = (q < 0) ? -1 : 1;
                auto coordinate = HexxagonUtil::Coordinate((q <= 0) ? r-size : r-size+q, q);
                if (std::find(excludedCoordinates.begin(), excludedCoordinates.end(), coordinate) != excludedCoordinates.end()) {
                    continue;
                }
                auto tile = setTile(coordinate, Tile(coordinate));
                auto tileShape = tile->getShape();
                float x = (q + size) * 1.5 * hexWidth / 2 + offsetX;
                float y = r * hexHeight + flipper * q * hexHeight / 2 + offsetY;

                // fmt::print("x: {}, y: {}\n", x, y);

                tileShape->setPosition(x, y);
                tile->setPixelPosition(x, y);
                // fmt::println("tile with coordinate ({}, {}) at x: {}, y: {}", coordinate.vertical, coordinate.diagonal, tile->getPixelPosition().first, tile->getPixelPosition().second);

            }
            if (q < 0) {
                rows++;
            } else {
                rows--;
            }
        }
    }

    auto Board::drawBoard(Hexxagon::WindowWrapper &window) -> void {

        if (!tiles.empty()) {  // to perform all the calculations only once
            // Put intermediate functions here ----
            //
            auto player = getPlayer(current_turn);
            if (player.has_value()) {
                auto selectedCoordinate = player.value()->getSelectedCoordinate();
                if (selectedCoordinate != nullptr) {
                    highlightSelectedCoordinate();
                    highlightSetOfCoordinates(findAdjacentCoordinatesOneStep(*selectedCoordinate),
                                              HexxagonUtil::CustomColors::Lime);
                    highlightSetOfCoordinates(findAdjacentCoordinatesTwoSteps(*selectedCoordinate), sf::Color::Yellow);
                }
            }
            //
            // -------------------------------------
            for (auto tile : tiles) {
                auto tileShape = tile.second.getShape();
                auto const [x, y] = tile.second.getPixelPosition();
                tileShape->setPosition(x, y);
                window.draw(*tileShape);
            }
        }
        drawPawns(window);
        // Sleep(10000);
    }


    auto Board::highlightSetOfCoordinates(std::vector<HexxagonUtil::Coordinate> const &coordinates, sf::Color color) -> void {
        for (auto coordinate : coordinates) {
            auto tile = getTile(coordinate);
            if (tile.has_value()) {
                if (*tile.value()->getStatus() == Tile::EMPTY) {
                    auto tileShape = tile.value()->getShape();
                    tileShape->setOutlineColor(color);
                    tileShape->setOutlineThickness(5);
                }
            }
        }
    }

    auto Board::highlightSelectedCoordinate() -> void {
        auto currentTurn = getCurrentTurn();
        auto player = currentTurn == PlayableSides::Side::RUBIES ? players[0] : players[1];
        if (player->getType() == PlayableSides::PlayerType::AI) {
            return;
        }
        auto selectedCoordinate = player->getSelectedCoordinate();
        if (selectedCoordinate == nullptr) {
            return;
        }
        auto tile = getTile(*selectedCoordinate);
        if (tile.has_value()) {
            auto tileShape = tile.value()->getShape();
            tileShape->setOutlineColor(HexxagonUtil::CustomColors::Teal);
            tileShape->setOutlineThickness(5);
        }
    }

    auto Board::removeSelectedHighlights() -> void {
        auto playerOpt = getPlayer(current_turn);
        if (!playerOpt.has_value()) {
            return;
        }
        auto player = playerOpt.value();
        auto selectedCoordinate = player->getSelectedCoordinate();
        if (selectedCoordinate != nullptr) {
            auto tile = getTile(*selectedCoordinate);
            if (tile.has_value()) {
                tile.value()->reset();
            }
            for (auto &adjacentCoordinate : findAdjacentCoordinatesOneStep(*selectedCoordinate)) {
                auto adjacentTile = getTile(adjacentCoordinate);
                if (adjacentTile.has_value()) {
                    adjacentTile.value()->reset();
                }
            }
            for (auto &adjacentCoordinateTwoSteps : findAdjacentCoordinatesTwoSteps(*selectedCoordinate)) {
                auto adjacentTile = getTile(adjacentCoordinateTwoSteps);
                if (adjacentTile.has_value()) {
                    adjacentTile.value()->reset();
                }
            }
        }
    }

    auto Board::drawPawns(Hexxagon::WindowWrapper &window) -> void {
        for (auto& tile : tiles) {
            auto tileStatus = *tile.second.getStatus();
            if (tileStatus == Tile::EMPTY) {
                continue;
            }
            auto pawnShape = getPawnShape(tileStatus == Tile::RUBY ? PlayableSides::RUBIES : PlayableSides::PEARLS);
            auto const [x, y] = tile.second.getPixelPosition();
            pawnShape.setPosition(x, y);
            window.draw(pawnShape);
        }
    }

    auto Board::clearBoard() -> void {
        for (auto tile : tiles) {
            // setTileStatus(tile.first, Tile::EMPTY);
        }
    }

    auto Board::findAdjacentCoordinatesOneStep(HexxagonUtil::Coordinate const &coordinate) -> std::vector<HexxagonUtil::Coordinate> {
        auto [diagonal, vertical] = coordinate;
        auto adjacentCoordinates = std::vector<HexxagonUtil::Coordinate>{
                {diagonal - 1, vertical},  // Up
                {diagonal + 1, vertical},  // Down
                {diagonal - 1, vertical - 1},  // Upper left
                {diagonal, vertical + 1},  // Upper right
                {diagonal, vertical - 1},  // Lower left
                {diagonal+1, vertical + 1},  // Lower right
        };
        return adjacentCoordinates;
    }

    auto Board::findAdjacentCoordinatesTwoSteps(HexxagonUtil::Coordinate const &coordinate) -> std::vector<HexxagonUtil::Coordinate> {
        auto [diagonal, vertical] = coordinate;
        auto adjacentCoordinates = std::vector<HexxagonUtil::Coordinate>{
                {diagonal - 2, vertical},  // Up
                {diagonal + 2, vertical},  // Down
                {diagonal - 2, vertical - 2},  // Upper left
                {diagonal, vertical + 2},  // Upper right
                {diagonal, vertical - 2},  // Lower left
                {diagonal+2, vertical + 2},  // Lower right

                // intermediate coordinates
                {diagonal - 1, vertical - 2},  // Left
                {diagonal + 1, vertical + 2},  // Right
                {diagonal - 1, vertical + 1},  // Upper right
                {diagonal - 2, vertical - 1},  // Upper left
                {diagonal + 1, vertical - 1},  // Lower left
                {diagonal + 2, vertical + 1},  // Lower right
        };
        return adjacentCoordinates;
    }

    auto BoardBuilder::setSize(short size) -> BoardBuilder& {
        board.size = size;
        return *this;
    }

    auto BoardBuilder::addPlayer(std::shared_ptr<PlayableSides> player) -> BoardBuilder& {
        board.players.push_back(std::move(player));
        return *this;
    }

    auto BoardBuilder::build() -> std::shared_ptr<Board> {
        return std::make_shared<Board>(std::move(board));
    }

} // Hexxagon