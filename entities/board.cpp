#include <optional>
#include <cmath>
#include <algorithm>
#include "board.h"
#include "tile.h"
#include "../main/window_wrapper.h"
#include "../main/game_manager.h"

namespace Hexxagon {
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

    auto Board::drawBoard(Hexxagon::WindowWrapper &window) -> void {
        auto const ex_tile = Tile({0,0});

        auto const hexWidth = 2 * ex_tile.getRadius();
        auto const hexHeight = std::sqrt(3) * ex_tile.getRadius();

        auto const [width, height] = window.getWindowDims();

        auto rows = size + 1;

        auto excludedCoordinates = std::vector<HexxagonUtil::Coordinate>{
            {-1, 0},
            {0, -1},
            {1, 0},
        };

        auto const offsetX = width / 2 - (hexWidth * rows) / 2;
        auto const offsetY = window.getWindowHeightPartition() * 2;
        // size = 4;
        for (int q = -size; q <= size; q++) {
            for (int r = 0; r < rows; r++) {
                auto const flipper = (q < 0) ? -1 : 1;
                auto coordinate = HexxagonUtil::Coordinate(q, r-size);
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
                window.draw(*tileShape);
                // fmt::println("tile with coordinate ({}, {}) at x: {}, y: {}", coordinate.vertical, coordinate.diagonal, tile->getPixelPosition().first, tile->getPixelPosition().second);

            }
            if (q < 0) {
                rows++;
            } else {
                rows--;
            }
        }
        // Sleep(10000);
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