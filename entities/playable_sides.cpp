#include "playable_sides.h"
#include "ai.h"
#include "player.h"

namespace Hexxagon {
    auto PlayableSides::getSide() const -> Side {
        return side;
    }

    auto PlayableSides::getOccupiedCoordinates() const -> std::set<HexxagonUtil::Coordinate> {
        return occupiedCoordinates;
    }

    auto PlayableSides::addOccupiedCoordinate(HexxagonUtil::Coordinate const &coordinate) -> void {
        occupiedCoordinates.insert(coordinate);
    }

    auto PlayableSides::removeOccupiedCoordinate(HexxagonUtil::Coordinate const &coordinate) -> void {
        occupiedCoordinates.erase(coordinate);
    }


    AI::AI(PlayableSides::Side side) : side(side) { }

    Player::Player() : side(PlayableSides::RUBIES) { }
    Player::Player(PlayableSides::Side alignment) : side(alignment) { }

    auto Player::getAlignment() const -> PlayableSides::Side {
        return side;
    }

    auto Player::setSelectedCoordinate(HexxagonUtil::Coordinate const &coordinate) -> void {
        selectedCoordinate = new HexxagonUtil::Coordinate(coordinate);
    }

    auto Player::clearSelectedCoordinate() -> void {
        delete selectedCoordinate;
        selectedCoordinate = nullptr;
    }

    auto Player::getSelectedCoordinate() const -> HexxagonUtil::Coordinate* {
        return selectedCoordinate;
    }

} // Hexxagon