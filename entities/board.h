#ifndef HEXAGON_BOARD_H
#define HEXAGON_BOARD_H

#include <map>
#include <optional>
#include <memory>
#include "../main/util.h"
#include "../main/window_wrapper.h"
#include "tile.h"
#include "playable_sides.h"
#include "move.h"

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

    public:
        Board() = default;

        static auto getGameMode() -> bool;

        static auto setGameMode(bool againstAi) -> void;

        auto getSize() const -> short;

        auto getPlayer(PlayableSides::Side side) -> std::optional<std::shared_ptr<PlayableSides>>;

        auto getTile(HexxagonUtil::Coordinate const &coordinate) const -> std::optional<Tile*>;

        auto getTiles() -> std::map<HexxagonUtil::Coordinate, Tile>*;

        auto addPawn(HexxagonUtil::Coordinate const &coordinate, PlayableSides::Side side) -> void;

        auto removePawn(HexxagonUtil::Coordinate const &coordinate) -> void;

        auto loadBoard() -> void;

        auto drawBoard(WindowWrapper &window) -> void;

        auto loadStartingPosition() -> void;

        void parseFen(std::string const &fen);

        void structureShapes();

        auto clearBoard() -> void;

        sf::CircleShape getPawnShape(PlayableSides::Side const &side);

        auto getCurrentTurn() -> PlayableSides::Side;

        auto findAdjacentCoordinatesOneStep(HexxagonUtil::Coordinate const &coordinate) -> std::vector<HexxagonUtil::Coordinate>;

        auto findAdjacentCoordinatesTwoSteps(HexxagonUtil::Coordinate const &coordinate) -> std::vector<HexxagonUtil::Coordinate>;

        auto removeSelectedHighlights() -> void;
    private:
        auto setTile(HexxagonUtil::Coordinate const &coordinate, Tile tile) -> Tile*;

        auto drawPawns(WindowWrapper &window) -> void;

        auto highlightSetOfCoordinates(std::vector<HexxagonUtil::Coordinate> const &coordinates, sf::Color color) -> void;

        auto highlightSelectedCoordinate() -> void;

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
