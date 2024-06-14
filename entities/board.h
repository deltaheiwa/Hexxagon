#ifndef HEXAGON_BOARD_H
#define HEXAGON_BOARD_H

#include <map>
#include <optional>
#include <memory>
#include "../main/util.h"
#include "../main/window_wrapper.h"
#include "tile.h"

namespace Hexxagon {
    class Board {
    private:
        friend class BoardBuilder;

        short size;
        std::map<HexxagonUtil::Coordinate, Tile> tiles = {};
        std::vector<std::shared_ptr<PlayableSides>> players;

        PlayableSides::Side current_turn = PlayableSides::Side::RUBIES;
    public:
        Board() = default;
        auto getSize() const -> short;

        auto getTile(HexxagonUtil::Coordinate const &coordinate) const -> std::optional<Tile*>;

        auto getTiles() -> std::map<HexxagonUtil::Coordinate, Tile>*;

        auto drawBoard(WindowWrapper &window) -> void;

        auto clearBoard() -> void;
    private:
        auto setTile(HexxagonUtil::Coordinate const &coordinate, Tile tile) -> Tile*;
    };

    class BoardBuilder {
    private:
        Board board;
    public:
        BoardBuilder() = default;

        auto setSize(short size) -> BoardBuilder&;

        auto addPlayer(std::shared_ptr<PlayableSides> player) -> BoardBuilder&;

        auto build() -> std::shared_ptr<Board>;
    };

} // Hexxagon

#endif //HEXAGON_BOARD_H
