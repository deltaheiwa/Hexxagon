#include "tile.h"
#include "pawn.h"

namespace Hexxagon {
    float const Tile::radius = 40;

    Tile::Tile(HexxagonUtil::Coordinate c) : status(TileStatus::EMPTY), coordinate(c) {
        structureShape();
    }

    Tile::Tile(HexxagonUtil::Coordinate c, TileStatus status) : status(status), coordinate(c) {
        structureShape();
        /*
        switch (status) {
            case TileStatus::EMPTY:
                shape.setFillColor(sf::Color::White);
                break;
            case TileStatus::RUBY:
                shape.setFillColor(sf::Color::Red);
                break;
            case TileStatus::PEARL:
                shape.setFillColor(sf::Color::White);
                break;
        }
        */
    }

    void Tile::structureShape() {
        shape.setPointCount(6);
        shape.setRadius(radius);
        shape.setRotation(90);
        shape.setOrigin(radius, radius);
        shape.setFillColor(HexxagonUtil::CustomColors::DarkPurple);
        shape.setOutlineThickness(2);
        shape.setOutlineColor(sf::Color::Black);
    }

    void Tile::addPawn(Pawn *pawn) {
        setStatus(pawn->getAlignment() == Pawn::PawnAlignment::RUBY ? TileStatus::RUBY : TileStatus::PEARL);
    }

    auto Tile::getCoordinate() const -> HexxagonUtil::Coordinate {
        return coordinate;
    }

    auto Tile::getRadius() const -> float {
        return radius;
    }

    auto Tile::getShape() const -> sf::CircleShape {
        return shape;
    }

    auto Tile::getStatus() const -> Tile::TileStatus {
        return status;
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

    }

    Pawn::Pawn(PawnAlignment alignment) : alignment(alignment) {

    }

    auto Pawn::getAlignment() const -> PawnAlignment {
        return alignment;
    }

    void Pawn::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        sf::CircleShape shape(20);
        switch (alignment) {
            case PawnAlignment::RUBY:
                shape.setFillColor(sf::Color::Red);
                break;
            case PawnAlignment::PEARL:
                shape.setFillColor(sf::Color::White);
                break;
        }
        target.draw(shape, states);
    }
} // Hexxagon