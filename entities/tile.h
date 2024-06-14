#ifndef HEXAGON_TILE_H
#define HEXAGON_TILE_H

#include "SFML/Graphics.hpp"
#include "../main/util.h"
#include "pawn.h"

namespace Hexxagon {

    class Tile {
    public:
        enum TileStatus {
            EMPTY,
            RUBY,
            PEARL
        };
        Tile() = default;
        Tile(HexxagonUtil::Coordinate c);
        Tile(HexxagonUtil::Coordinate c, TileStatus status);

        HexxagonUtil::Coordinate getCoordinate() const;
        float getRadius() const;
        TileStatus getStatus() const;
        auto getShape() -> sf::CircleShape*;
        std::pair<float, float> getPixelPosition() const;
        void setPixelPosition(float &x, float &y);
        void setStatus(TileStatus status);
    private:
        TileStatus status;
        sf::CircleShape shape;
        HexxagonUtil::Coordinate coordinate;
        float x;
        float y;
        static constexpr float radius = 50.0f;

        void structureShape();

        void addPawn(Pawn *pawn);

    };

} // Hexxagon

#endif //HEXAGON_TILE_H
