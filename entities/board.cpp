#include <optional>
#include <cmath>
#include <algorithm>
#include "board.h"
#include "tile.h"
#include "../main/window_wrapper.h"
#include "../main/game.h"

namespace Hexxagon {
    short Board::size = 4;

    Board::Board() {
        for (short p = -1; p < 2; p++) {
            if (p == 0) continue;
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    auto coordinate = HexxagonUtil::Coordinate(i*p, j*p);
                    Tile tile = Tile(HexxagonUtil::Coordinate(i*p, j*p));
                    setTile(coordinate, tile); // Essentially, this is a mask for the board
                }
            }
        }
    }

    auto Board::getInstance() -> Board& {
        static Board instance = Board();
        return instance;
    }

    auto Board::getTile(HexxagonUtil::Coordinate const &coordinate) const -> std::optional<Tile> {
        // https://en.cppreference.com/w/cpp/utility/optional
        if (!tiles.contains(coordinate)) {
            return std::nullopt;
        }
        return tiles.at(coordinate);
    }

    auto Board::setTile(const HexxagonUtil::Coordinate &coordinate, Tile &tile) -> void {
        tiles[coordinate] = tile;
    }


    auto Board::drawBoard(Hexxagon::WindowWrapper &window) -> void {
        auto ex_tile = getTile(HexxagonUtil::Coordinate(0, 0));
        auto hexWidth = 2 * ex_tile->getRadius();
        auto hexHeight = std::sqrt(3) * ex_tile->getRadius();

        auto windowDims = window.getWindowDims();

        auto offsetX = 1000;
        auto offsetY = 500;

        auto windowDiv = window.getWindowHeightPartition();
        // size = 4;
        for (int q = 0; q <= size*2; q++) {
            for (int r = std::max(-size, -q - size); r <= std::min((int)(size), -q + size); r++) {
                auto coordinate = HexxagonUtil::Coordinate(q, r);
                if (auto tile = getTile(coordinate); tile.has_value()) {
                    auto tileShape = tile->getShape();
                    float x = (q * 1.5 * ex_tile->getRadius()) + offsetX;
                    float y = (r * hexHeight + (q % 2) * hexHeight / 2) + offsetY;

                    tileShape.setPosition(x, y + windowDiv);
                    window.draw(tileShape);
                }
            }
        }
        /*
        for (int xCoord = 0; xCoord < size*2; xCoord++) {
            for (int yCoord = 0; yCoord < size*2; yCoord++) {
                auto coordinate = HexxagonUtil::Coordinate(xCoord - 4, yCoord - 4);
                if (auto tile = getTile(coordinate); tile.has_value()) {
                    auto tileShape = tile->getShape();
                    // if (xCoord > size) { xCoord = xCoord * (-1); offsetY = offsetY + hexHeight / 2; }

                    auto x = xCoord * (1.5 * ex_tile->getRadius()) + offsetX;
                    auto y = yCoord * hexHeight + offsetY;

                    if (xCoord % 2 != 0) {
                        y += hexHeight / 2;
                    }

                    tileShape.setPosition(x, y + windowDiv);

                    auto x = xCoord * hexWidth + offsetX;
                    auto y = yCoord * hexHeight + offsetY;
                    if (xCoord % 2 == 1) { y += hexHeight / 2; x -= (ex_tile->getRadius() / 2) * xCoord; }
                    else if (xCoord % 2 == 0 && xCoord != 0) { x -= ex_tile->getRadius(); }
                    tileShape.setPosition(x + windowDiv, y);
                    window.draw(tileShape);
                }
            }
        }*/
    }

    auto Board::clearBoard() -> void {
        for (auto tile : tiles) {
            // setTileStatus(tile.first, Tile::EMPTY);
        }
    }


} // Hexxagon