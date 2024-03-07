#include <editor/editor.hpp>

namespace Editor{
void
Editor::uiTexture() {
    ImGui::ShowDemoWindow();

    if (ImGui::Begin("Textures", &mWindowOpen["Textures"], ImGuiWindowFlags_AlwaysAutoResize)) {
        static int currentItem;

        std::vector<std::string> elements = {"Hello", "World"};
        if(ImGui::BeginListBox("##Textures")){
            for(int i = 0; i < elements.size(); i++){
                const bool selected = (currentItem == i);
                if(ImGui::Selectable(elements[i].c_str(), selected)){
                    currentItem = i;
                }
                if(selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndListBox();
        }
        ImGui::End();
    }

}
}