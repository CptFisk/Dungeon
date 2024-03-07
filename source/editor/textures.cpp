#include <editor/editor.hpp>

namespace Editor{
void
Editor::uiTexture() {
    if (ImGui::Begin("Textures", &mWindowOpen["Textures"], ImGuiWindowFlags_AlwaysAutoResize)) {
        static int currentItem;

        if(ImGui::BeginListBox("##Textures")){
            for(int i = 0; i < mTextures.size(); i++){
                const bool selected = (currentItem == i);
                if(ImGui::Selectable(mTextures[i].c_str(), selected)){
                    currentItem = i;
                    mSelectedTexture = mTextures[i];
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