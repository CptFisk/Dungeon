#include <editor/editor.hpp>
#include <editor/utility/mouse.hpp>
#include <misc/cpp/imgui_stdlib.h>
#include <imgui.h>

namespace Editor {

void mouseButton(Mouse& current, const Mouse& state, const std::string& text){
    ImVec2 buttonSize(ImGui::GetContentRegionAvail().x, 0);
    if(current == state){
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.8f, 0.4f, 1.0f });
    }else{
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.8f, 0.8f, 1.0f });
    }
    if(ImGui::Button(text.c_str(), buttonSize))
        current = state;
    ImGui::PopStyleColor(1);
}

void
Editor::uiMouse(typeWindowCovering& area, bool& open) {
    if (ImGui::Begin("Mouse", &open, ImGuiWindowFlags_AlwaysAutoResize)) {

        ImVec2 buttonSize(ImGui::GetContentRegionAvail().x, 0);
        ImGui::SeparatorText("Graphical");
        mouseButton(mMouse, Mouse::DEFAULT, "None");
        mouseButton(mMouse, Mouse::REMOVE, "Remove");

        ImGui::SeparatorText("Tiletype");
        mouseButton(mMouse, Mouse::TEXTURE, "Texture");
        mouseButton(mMouse, Mouse::WALL, "Wall");
        mouseButton(mMouse, Mouse::OBSTACLE, "Obstacle");
        mouseButton(mMouse, Mouse::PLAYER_SPAWN, "Player spawn");
        mouseButton(mMouse, Mouse::DOOR, "Door");
        mouseButton(mMouse, Mouse::WARP, "Warp");
        area = { ImGui::GetWindowPos(), ImGui::GetWindowSize() };
        ImGui::End();
    }

    if(!open)
        hideElement("Mouse");
}
}