#include <editor/utility/mouse.hpp>
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

}