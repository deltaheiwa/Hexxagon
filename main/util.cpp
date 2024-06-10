#include "util.h"

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
    sf::Color const CustomColors::DarkRed = sf::Color(139,0,0);
}
