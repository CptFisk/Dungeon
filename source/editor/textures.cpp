#include <editor/editor.hpp>
#include <misc/cpp/imgui_stdlib.h>
#include <graphics/graphics.hpp>

namespace Editor{

void Editor::removeSpecificTexture(const std::string& name) {
    bool exist = false;
    auto texture =  GET_SIMPLE(name);
    if(texture == nullptr)
        return;
    for(auto &tile : editorTiles){
        if(tile->elementExist(texture->Texture))
            exist = true;
    }
}


void
Editor::uiTexture() {
    if (ImGui::Begin("Textures", &mWindowOpen["Textures"], ImGuiWindowFlags_AlwaysAutoResize)) {
        static int currentItem;
        static std::string filter;
        ImGui::InputText("##Filter", &filter);
        if(ImGui::BeginListBox("##Textures")){
            for(int i = 0; i < mTextures.size(); i++){
                if(mTextures[i].second.find(filter) != std::string::npos) {
                    const bool selected = (currentItem == i);
                    if (ImGui::Selectable(mTextures[i].second.c_str(), selected)) {
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