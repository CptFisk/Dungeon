#pragma once
#include <string>

namespace Editor {

/**
 * Different modes the mouse can have in editor mode
 */
enum class Mouse {
    DEFAULT,      // Default, no action when you click
    REMOVE,       // Remove all states and links to the tile
    TEXTURE,      // Add a standard texture to the tile
    UP,           // Add a warp up
    DOWN,         // Add a warp down
    WALL,         // Make a wall
    OBSTACLE,     // Make an obstacle
    PLAYER_SPAWN, // Set player spawn
    DOOR,         // Create a door
    WARP,          // Create a warp-zone.
    TOP_LAYER      //Layer that the player can walk under
};

/**
 * @brief Return a color code that is connected to each mouse state
 * @param mouse Current mouse state
 * @return Colour code in format of #XXXXXX
 */
[[nodiscard]] constexpr std::string
getMouseColorCode(const Mouse& mouse) {
    switch (mouse) {
        case Mouse::DEFAULT:
        case Mouse::REMOVE:
        case Mouse::TEXTURE:
            return ""; // They don't have a colour code
        case Mouse::UP:
            return "#C0E6F5";
        case Mouse::DOWN:
            return "#FFFF66";
        case Mouse::WALL:
            return "#D86DCD";
        case Mouse::OBSTACLE:
            return "#BE5014";
        case Mouse::PLAYER_SPAWN:
            return "#E8E8E8";
        case Mouse::DOOR:
            return "#000000";
        case Mouse::WARP:
            return "#8ED973";
        case Mouse::TOP_LAYER:
            return "#8960CF";
        default:
            return "";
    }
}

void mouseButton(Mouse& current, const Mouse& state, const std::string& text);



}