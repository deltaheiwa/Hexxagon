#ifndef HEXAGON_TILE_H
#define HEXAGON_TILE_H

#include "SFML/Graphics.hpp"
#include "../main/util.h"

namespace Hexxagon {
    class Tile {
    public:
        enum TileStatus {
            EMPTY,
            RUBY,
            PEARL
        };
    private:
        TileStatus status;
        sf::CircleShape shape;
        HexxagonUtil::Coordinate coordinate;
        float x;
        float y;
        sf::Color currentFillColor;
        sf::Color currentOutlineColor;
        static constexpr float radius = 50.0f;

        void structureShape();
    public:
        Tile() = default;
        Tile(HexxagonUtil::Coordinate c);
        Tile(HexxagonUtil::Coordinate c, TileStatus status);

        std::string getTileStatusString() {
            switch (status) {
                case TileStatus::EMPTY:
                    return "EMPTY";
                case TileStatus::RUBY:
                    return "RUBY";
                case TileStatus::PEARL:
                    return "PEARL";
                default:
                    return "UNKNOWN";
            }
        }

        HexxagonUtil::Coordinate getCoordinate() const;

        float getRadius() const;

        auto getStatus() const -> TileStatus;

        auto getShape() -> sf::CircleShape*;

        std::pair<float, float> getPixelPosition() const;

        void setPixelPosition(float &x, float &y);

        void setStatus(TileStatus status);

        void setFillColor(sf::Color color);

        void setOutlineColor(sf::Color color);

        void highlightLastMove();

        void restoreColorsFromLastMove();

        void reset();
    };

} // Hexxagon

#endif //HEXAGON_TILE_H
