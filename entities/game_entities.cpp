#include "tile.h"
#include <cmath>

namespace Hexxagon {
    const float HexagonShape::pi = 3.1415;

    std::size_t HexagonShape::getPointCount() const {
        return 6;
    }

    sf::Vector2f HexagonShape::getPoint(std::size_t index) const {
        float angle = 2 * pi * index / 6;
        float x = std::cos(angle) * m_radius;
        float y = std::sin(angle) * m_radius;
        return {m_radius + x, m_radius + y};
    }

    Tile::Tile(HexxagonUtil::Coordinate c) : status(TileStatus::EMPTY), shape(HexagonShape(getRadius())), coordinate(c){
        structureShape();
    }

    Tile::Tile(HexxagonUtil::Coordinate c, TileStatus status) : status(status), shape(HexagonShape(getRadius())), coordinate(c) {
        structureShape();
    }

    void Tile::structureShape() {
        // shape.setRotation(90);
        shape.setOrigin(getRadius(), getRadius());
        shape.setOutlineThickness(-2);
        setFillColor(HexxagonUtil::CustomColors::DarkPurple);
        setOutlineColor(HexxagonUtil::CustomColors::PurplishPink);
    }

    auto Tile::getCoordinate() const -> HexxagonUtil::Coordinate {
        return coordinate;
    }

    auto Tile::getRadius() -> float {
        return radius;
    }

    auto Tile::getShape() -> HexagonShape* {
        return &shape;
    }

    auto Tile::getStatus() const -> Tile::TileStatus {
        return status;
    }


    auto Tile::getPixelPosition() const -> std::pair<float, float> {
        return std::make_pair(x, y);
    }

    void Tile::setPixelPosition(float &x, float &y) {
        this->x = x;
        this->y = y;
    }

    void Tile::setStatus(Tile::TileStatus set_status) {
        this->status = set_status;
    }

    void Tile::setFillColor(sf::Color color) {
        shape.setFillColor(color);
        currentFillColor = color;
    }

    void Tile::setOutlineColor(sf::Color color) {
        shape.setOutlineColor(color);
        currentOutlineColor = color;
    }

    void Tile::highlightLastMove() {
        shape.setFillColor(HexxagonUtil::CustomColors::lightenColor(HexxagonUtil::CustomColors::PurplishPink, 0.5));
        shape.setOutlineColor(HexxagonUtil::CustomColors::lightenColor(HexxagonUtil::CustomColors::DarkPurple, 0.5));
    }

    void Tile::restoreColorsFromLastMove() {
        shape.setFillColor(HexxagonUtil::CustomColors::DarkPurple);
        shape.setOutlineColor(HexxagonUtil::CustomColors::PurplishPink);
    }

    void Tile::reset() {
        shape.setFillColor(currentFillColor);
        shape.setOutlineColor(currentOutlineColor);
        shape.setOutlineThickness(2);
    }
} // Hexxagon