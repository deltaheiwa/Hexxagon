#include "tile.h"

namespace Hexxagon {
    Tile::Tile(HexxagonUtil::Coordinate c) : status(TileStatus::EMPTY), coordinate(c) {
        structureShape();
    }

    Tile::Tile(HexxagonUtil::Coordinate c, TileStatus status) : status(status), coordinate(c) {
        structureShape();
    }

    void Tile::structureShape() {
        shape.setPointCount(6);
        shape.setRadius(radius);
        shape.setRotation(90);
        shape.setOrigin(radius, radius);
        shape.setFillColor(HexxagonUtil::CustomColors::DarkPurple);
        shape.setOutlineThickness(2);
        shape.setOutlineColor(HexxagonUtil::CustomColors::PurplishPink);
    }

    auto Tile::getCoordinate() const -> HexxagonUtil::Coordinate {
        return coordinate;
    }

    auto Tile::getRadius() const -> float {
        return radius;
    }

    auto Tile::getShape() -> sf::CircleShape* {
        return &shape;
    }

    auto Tile::getStatus() -> Tile::TileStatus* {
        return &status;
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
} // Hexxagon