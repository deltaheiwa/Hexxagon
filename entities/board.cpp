#include <optional>
#include <cmath>
#include <algorithm>
#include "board.h"
#include "tile.h"
#include "../main/window_wrapper.h"
#include "../main/game_manager.h"
#include "fmt/core.h"

namespace Hexxagon {
    bool Board::is_against_ai = false;
    std::string Board::starting_position = "r3p/6/7/8/p7r/8/7/6/r3p";

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
        tiles[coordinate] = tile;
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

    auto Board::parseFen(std::string const &fen) -> void {
        auto columns = HexxagonUtil::splitString(fen, '/');
        auto player1 = players[0];
        auto player2 = players[1];

        for (int columnIndex = 0; columnIndex < columns.size(); columnIndex++) {
            auto x = -size;
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
                    }
                    c == 'r' ? player1->addOccupiedCoordinate({x, y}) : player2->addOccupiedCoordinate({x, y});
                    fmt::println("Setting tile at ({}, {}) to {}", x, y, c == 'r' ? "RUBY" : "PEARL");
                    x++;
                } else {
                    fmt::println("Invalid character in FEN: {}", c);
                }
            }

        }
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

    auto Board::loadBoard() -> void {
        auto const ex_tile = Tile({0,0});

        auto const hexWidth = 2 * ex_tile.getRadius();
        auto const hexHeight = std::sqrt(3) * ex_tile.getRadius();

        auto window = GameManager::getInstance()->getWindow();

        auto const [width, height] = window->getWindowDims();

        auto rows = size + 1;

        auto excludedCoordinates = std::vector<HexxagonUtil::Coordinate>{
                {-1, 0},
                {0, -1},
                {0, 1},
        };  // holes in the middle of the board

        auto const offsetX = width / 2 - (hexWidth * rows) / 2;
        auto const offsetY = window->getWindowHeightPartition() * 2;
        // size = 4;
        for (int q = -size; q <= size; q++) {
            for (int r = 0; r < rows; r++) {
                auto const flipper = (q < 0) ? -1 : 1;
                auto coordinate = HexxagonUtil::Coordinate(r-size, q);
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