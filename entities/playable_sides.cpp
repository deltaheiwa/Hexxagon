#include "playable_sides.h"
#include "ai.h"
#include "player.h"
#include "../main/game_manager.h"

namespace Hexxagon {
    PlayableSides::PlayableSides(Side side, PlayerType type) : side(side), type(type) { }

    auto PlayableSides::getSide() -> PlayableSides::Side {
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


    AI::AI(PlayableSides::Side side) : PlayableSides(side, PlayerType::AI) { }

    Player::Player() : PlayableSides(Side::RUBIES, PlayerType::HUMAN) { }
    Player::Player(PlayableSides::Side alignment) : PlayableSides(alignment, PlayerType::HUMAN) { }

    auto Player::setSelectedCoordinate(HexxagonUtil::Coordinate const &coordinate) -> void {
        auto currentlySelectedCoordinate = getSelectedCoordinate();
        if (currentlySelectedCoordinate != nullptr) {
            GameManager::getInstance()->getBoard()->getTile(*currentlySelectedCoordinate).value()->reset();
            for (auto &adjacentCoordinate : GameManager::getInstance()->getBoard()->findAdjacentCoordinatesOneStep(*currentlySelectedCoordinate)) {
                auto adjacentTile = GameManager::getInstance()->getBoard()->getTile(adjacentCoordinate);
                if (adjacentTile.has_value()) {
                    adjacentTile.value()->reset();
                }
            }
            for (auto &adjacentCoordinateTwoSteps : GameManager::getInstance()->getBoard()->findAdjacentCoordinatesTwoSteps(*currentlySelectedCoordinate)) {
                auto adjacentTile = GameManager::getInstance()->getBoard()->getTile(adjacentCoordinateTwoSteps);
                if (adjacentTile.has_value()) {
                    adjacentTile.value()->reset();
                }
            }
        }
        selectedCoordinate = new HexxagonUtil::Coordinate(coordinate);
    }

    auto Player::clearSelectedCoordinate() -> void {
        selectedCoordinate = nullptr;
    }

    auto Player::getSelectedCoordinate() const -> HexxagonUtil::Coordinate* {
        return selectedCoordinate;
    }

} // Hexxagon