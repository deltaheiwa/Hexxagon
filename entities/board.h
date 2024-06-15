#ifndef HEXAGON_BOARD_H
#define HEXAGON_BOARD_H

#include <map>
#include <optional>
#include <memory>
#include "../main/util.h"
#include "../main/window_wrapper.h"
#include "tile.h"
#include "playable_sides.h"

namespace Hexxagon {
    class Board {
    private:
        friend class BoardBuilder;
        static bool is_against_ai;
        static std::string starting_position;

        short size;
        std::map<HexxagonUtil::Coordinate, Tile> tiles = {};
        std::vector<std::shared_ptr<PlayableSides>> players;

        PlayableSides::Side current_turn = PlayableSides::Side::RUBIES;
        // std::pair<Coordinate, Coordinate> last_move;
    public:
        Board() = default;

        static auto getGameMode() -> bool;

        static auto setGameMode(bool againstAi) -> void;

        auto getSize() const -> short;

        auto getTile(HexxagonUtil::Coordinate const &coordinate) const -> std::optional<Tile*>;

        auto getTiles() -> std::map<HexxagonUtil::Coordinate, Tile>*;

        auto loadBoard() -> void;

        auto drawBoard(WindowWrapper &window) -> void;

        auto loadStartingPosition() -> void;

        void parseFen(std::string const &fen);

        void structureShapes();

        auto clearBoard() -> void;

        sf::CircleShape getPawnShape(PlayableSides::Side const &side);

        auto getCurrentTurn() -> PlayableSides::Side;
    private:
        auto setTile(HexxagonUtil::Coordinate const &coordinate, Tile tile) -> Tile*;

        auto drawPawns(WindowWrapper &window) -> void;

        sf::CircleShape rubyShape;
        sf::CircleShape pearlShape;
        static constexpr float pawnRadius = 20.0f;
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
