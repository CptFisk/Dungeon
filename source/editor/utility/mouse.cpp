#include <editor/utility/mouse.hpp>

namespace Editor{
std::string
getMouseColorCode(const Mouse& mouse){
    switch (mouse) {
        case Mouse::DEFAULT:
        case Mouse::CLEAR_ALL:
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
        case Mouse::NPC_WALL:
            return "#FFF4AE";
        case Mouse::SPARE:
            return "#E8E8E8";
        case Mouse::DOOR:
            return "#000000";
        case Mouse::WARP:
            return "#8ED973";
        case Mouse::TOP_LAYER:
            return "#8960CF";
        case Mouse::LIGHTNING:
            return "#C8BFE7";
        default:
            return "";
    }
}
}