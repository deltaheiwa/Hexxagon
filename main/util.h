#ifndef HEXAGON_UTIL_H
#define HEXAGON_UTIL_H

#include <string>
#include <tuple>
#include <vector>
#include "SFML/Graphics/Color.hpp"

namespace HexxagonUtil {
    struct Coordinate {
        int diagonal;
        int vertical;

        // Needed to use Coordinate as a key in std::map
        bool operator<(const Coordinate &other) const;

        bool operator==(const Coordinate &other) const;
    };

    class CustomColors {
    public:
        static sf::Color const PurplishPink;
        static sf::Color const DarkPurple;
        static sf::Color const Teal;
        static sf::Color const SoftPink;
        static sf::Color const SoftLightBlue;
        static sf::Color const DarkRed;
    };

    float generateRandomNumber(float const &floor, float const &ceiling);

    auto splitString(std::string const &str, char const &delimiter) -> std::vector<std::string>;
}

#endif //HEXAGON_UTIL_H
