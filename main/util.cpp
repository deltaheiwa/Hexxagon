#include "util.h"

#include <random>
#include <tuple>
#include <sstream>

namespace HexxagonUtil {
    bool Coordinate::operator<(const Coordinate &other) const {
        return std::tie(vertical, diagonal) < std::tie(other.vertical, other.diagonal);
    }

    bool Coordinate::operator==(const Coordinate &other) const {
        return vertical == other.vertical && diagonal == other.diagonal;
    }

    sf::Color const CustomColors::PurplishPink = sf::Color(176,0,176);
    sf::Color const CustomColors::DarkPurple = sf::Color(100,0,100);
    sf::Color const CustomColors::Teal = sf::Color(0,176,176);
    sf::Color const CustomColors::SoftPink = sf::Color(255,192,203);
    sf::Color const CustomColors::SoftLightBlue = sf::Color(209,223,246);
    sf::Color const CustomColors::DarkRed = sf::Color(139,0,0);

    float generateRandomNumber(float const &floor, float const &ceiling) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> distribution(floor, ceiling);
        return distribution(gen);
    }

    std::vector<std::string> splitString(const std::string &str, char const &delimiter) {
        std::vector<std::string> parts;
        std::string part;
        std::stringstream ss(str);

        while (std::getline(ss, part, delimiter)) {
            parts.push_back(part);
        }

        return parts;
    }
}
