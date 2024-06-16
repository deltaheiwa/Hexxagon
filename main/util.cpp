#include "util.h"
#include "fmt/core.h"

#include <random>
#include <tuple>
#include <sstream>
#include <filesystem>

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
    sf::Color const CustomColors::Lime = sf::Color(0,255,127);

    sf::Color CustomColors::lightenColor(const sf::Color &color, float factor) {
        auto red = (sf::Uint8)(color.r + (255.0f - color.r) * factor);
        auto green = (sf::Uint8)(color.g + (255.0f - color.g) * factor);
        auto blue = (sf::Uint8)(color.b + (255.0f - color.b) * factor);

        return {red, green, blue, color.a};
    }

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

    std::vector<std::filesystem::path> getFilesInDirectory(const std::filesystem::path& directoryPath) {
        std::vector<std::filesystem::path> files;

        try {
            for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
                if (std::filesystem::is_regular_file(entry.path())) {
                    files.push_back(entry.path());
                }
            }
        } catch (const std::filesystem::filesystem_error& e) {
            fmt::println("Filesystem error: {}", e.what());
        } catch (const std::exception& e) {
            fmt::println("General error: {}\n", e.what());
        }

        return files;
    }
}
