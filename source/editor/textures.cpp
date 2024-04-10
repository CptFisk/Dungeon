#include <editor/editor.hpp>
#include <misc/cpp/imgui_stdlib.h>

namespace Editor{
void
Editor::uiTexture() {
    if (ImGui::Begin("Textures", &mWindowOpen["Textures"], ImGuiWindowFlags_AlwaysAutoResize)) {
        static int currentItem;
        static std::string filter;
        ImGui::InputText("##Filter", &filter);
        if(ImGui::BeginListBox("##Textures")){
            for(int i = 0; i < mTextures.size(); i++){
                if(mTextures[i].find(filter) != std::string::npos) {
                    const bool selected = (currentItem == i);
                    if (ImGui::Selectable(mTextures[i].c_str(), selected)) {
                        currentItem      = i;
                        mSelectedTexture = mTextures[i];
                    }
                    if (selected)
                        ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndListBox();
        }
        mWindows["Textures"] = { ImGui::GetWindowPos(), ImGui::GetWindowSize() };
        ImGui::End();
    }

    if(!mWindowOpen["Textures"])
        hideElement("Textures");

}
}