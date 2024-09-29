#pragma once
#include <imgui.h>
#include <string>
namespace Editor {

/**
 * Different modes the mouse can have in editor mode
 */
enum Mouse {
    DEFAULT,      // Default, no action when you click
    CLEAR_ALL,    // Remove all states and links to the tile
    CLEAR_LATEST, // Remove the latest added graphic
    CLEAR_TYPE,   // Remove types such as monster, up/down wall etc.
    TEXTURE,      // Add a standard texture to the tile
    UP,           // Add a warp up
    DOWN,         // Add a warp down
    WALL,         // Make a wall
    OBSTACLE,     // Make an obstacle
    SPARE,        // Previously player spawn
    DOOR,         // Create a door
    WARP,         // Create a warp-zone.
    TOP_LAYER,    // Layer that the player can walk under
    LIGHTNING,    // Add lightning effects
    MONSTER,      // Bind a monster to a tile
    NPC           // Bind a npc to a tile
};

/**
 * @brief Return a color code that is connected to each mouse state
 * @param mouse Current mouse state
 * @return Colour code in format of #XXXXXX
 */
[[nodiscard]] std::string
getMouseColorCode(const Mouse& mouse);

template<typename T>
bool
mouseButton(T& current, const T& state, const std::string& text) {
    bool   clicked = false;
    ImVec2 buttonSize(ImGui::GetContentRegionAvail().x, 0);
    if (current == state) {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.8f, 0.4f, 1.0f });
    } else {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.8f, 0.8f, 1.0f });
    }
    if (ImGui::Button(text.c_str(), buttonSize)) {
        current = state;
        clicked = true;
    }
    ImGui::PopStyleColor(1);
    return clicked;
}
}