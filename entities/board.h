#ifndef HEXAGON_BOARD_H
#define HEXAGON_BOARD_H

#include <map>
#include <optional>
#include "../main/util.h"
#include "../main/window_wrapper.h"
#include "tile.h"

namespace Hexxagon {
    class Board {
    public:
        static auto getInstance() -> Board&;

        auto getTile(HexxagonUtil::Coordinate const &coordinate) const -> std::optional<Tile>;
        auto setTile(HexxagonUtil::Coordinate const &coordinate, Tile &tile) -> void;

        auto drawBoard(WindowWrapper &window) -> void;
        auto clearBoard() -> void;
    private:
        static short size;
        std::map<HexxagonUtil::Coordinate, Tile> tiles;
        Board();


    };

} // Hexxagon

#endif //HEXAGON_BOARD_H
