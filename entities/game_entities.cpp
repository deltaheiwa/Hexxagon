#include "tile.h"
#include "pawn.h"

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

    void Tile::addPawn(Pawn *pawn) {
        setStatus(pawn->getAlignment() == PlayableSides::RUBIES ? TileStatus::RUBY : TileStatus::PEARL);
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
        switch (status) {
            case TileStatus::EMPTY:
                shape.setFillColor(HexxagonUtil::CustomColors::DarkPurple);
                break;
            case TileStatus::RUBY:
                shape.setFillColor(sf::Color::Red);
                break;
            case TileStatus::PEARL:
                shape.setFillColor(sf::Color::White);
                break;
        }
    }


    Pawn::Pawn() {
        structureShape();
    }

    Pawn::Pawn(PlayableSides::Side alignment) : alignment(alignment) {
        structureShape();
    }

    auto Pawn::getAlignment() const -> PlayableSides::Side {
        return alignment;
    }

    void Pawn::structureShape() {
        switch (alignment) {
            case PlayableSides::RUBIES:
                shape.setFillColor(sf::Color::Red);
                shape.setOutlineThickness(4);
                shape.setOutlineColor(HexxagonUtil::CustomColors::DarkRed);
                shape.setPointCount(6);
                break;
            case PlayableSides::PEARLS:
                shape.setFillColor(sf::Color::White);
                shape.setOutlineThickness(3);
                shape.setOutlineColor(HexxagonUtil::CustomColors::SoftPink);
                break;
        }
        shape.setRadius(radius);
    }
} // Hexxagon