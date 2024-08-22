#ifndef HEXAGON_TILE_H
#define HEXAGON_TILE_H

#include "SFML/Graphics.hpp"
#include "../main/util.h"

namespace Hexxagon {
    class HexagonShape : public sf::Shape {
    public:
        explicit HexagonShape(const float radius) : m_radius(radius) {
            update();
        }

        std::size_t getPointCount() const override;

        sf::Vector2f getPoint(std::size_t index) const override;

    private:
        float m_radius;
        static const float pi;
    };

    class Tile {
    public:
        enum TileStatus {
            EMPTY,
            RUBY,
            PEARL
        };
    private:
        TileStatus status;
        HexagonShape shape;
        HexxagonUtil::Coordinate coordinate;
        float x;
        float y;
        sf::Color currentFillColor;
        sf::Color currentOutlineColor;
        static constexpr float radius = 50.0f;

        void structureShape();
    public:
        Tile(): shape(HexagonShape(radius)) {}

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

        static float getRadius() ;

        auto getStatus() const -> TileStatus;

        auto getShape() -> HexagonShape*;

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
