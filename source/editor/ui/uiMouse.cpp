#include <editor/editor.hpp>

namespace Editor {

void
Editor::uiMouse(typeWindowCovering& area, bool& open, Mouse& mouse) {
    if (ImGui::Begin("Mouse", &open, ImGuiWindowFlags_AlwaysAutoResize)) {

        ImGui::SeparatorText("Graphical");
        mouseButton(mouse, Mouse::DEFAULT, "None");
        if (mouseButton(mouse, Mouse::LIGHTNING, "Lightning"))
            displayElement("Lightning");
        ImGui::SeparatorText("Clearing");
        mouseButton(mouse, Mouse::CLEAR_ALL, "Clear all");
        mouseButton(mouse, Mouse::CLEAR_LATEST, "Clear last");
        mouseButton(mouse, Mouse::CLEAR_TYPE, "Clear types");
        ImGui::SeparatorText("Tiletype");
        mouseButton(mouse, Mouse::TEXTURE, "Texture");
        mouseButton(mouse, Mouse::TOP_LAYER, "Top layer");
        mouseButton(mouse, Mouse::WALL, "Wall");
        mouseButton(mouse, Mouse::OBSTACLE, "Obstacle");
        mouseButton(mouse, Mouse::NPC_WALL, "NPC-Wall");

        ImGui::SeparatorText("Interaction");
        mouseButton(mouse, Mouse::UP, "Up");
        mouseButton(mouse, Mouse::DOWN, "Down");
        mouseButton(mouse, Mouse::DOOR, "Door");
        mouseButton(mouse, Mouse::WARP, "Warp");
        if (mouseButton(mouse, Mouse::MONSTER, "Monster"))
            displayElement("Monster");
        if (mouseButton(mouse, Mouse::NPC, "Npc"))
            displayElement("Npc");

        area = { ImGui::GetWindowPos(), ImGui::GetWindowSize() };
        ImGui::End();
    }

    if (!open)
        hideElement("Mouse");
}
}