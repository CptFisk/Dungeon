#include <editor/editor.hpp>

namespace Editor {

void
Editor::uiMouse(typeWindowCovering& area, bool& open, Mouse& mouse) {
    if (ImGui::Begin("Mouse", &open, ImGuiWindowFlags_AlwaysAutoResize)) {

        ImGui::SeparatorText("Graphical");
        mouseButton(mouse, Mouse::DEFAULT, "None");
        mouseButton(mouse, Mouse::REMOVE, "Remove");

        ImGui::SeparatorText("Tiletype");
        mouseButton(mouse, Mouse::TEXTURE, "Texture");
        mouseButton(mouse, Mouse::TOP_LAYER, "Top layer");
        mouseButton(mouse, Mouse::WALL, "Wall");
        mouseButton(mouse, Mouse::OBSTACLE, "Obstacle");
        ImGui::SeparatorText("Interaction");
        mouseButton(mouse, Mouse::UP, "Up");
        mouseButton(mouse, Mouse::DOWN, "Down");
        mouseButton(mouse, Mouse::DOOR, "Door");
        mouseButton(mouse, Mouse::WARP, "Warp");
        area = { ImGui::GetWindowPos(), ImGui::GetWindowSize() };
        ImGui::End();
    }

    if (!open)
        hideElement("Mouse");
}
}