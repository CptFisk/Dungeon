#include <editor/editor.hpp>
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include <algorithm>

namespace Editor {
void
Editor::uiAssets() {

    if (ImGui::Begin("Assets", &mWindowOpen["Assets"], ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Assets");
        for(auto& element : fileAssets.Assets){
            ImGui::InputText("##", &element, ImGuiInputTextFlags_ReadOnly);
            ImGui::SameLine();
            if(ImGui::Button(("Delete##" + element).c_str())){
                for(auto it = fileAssets.Assets.begin(); it != fileAssets.Assets.end(); ++it){
                    if(*it == element){
                        fileAssets.Assets.erase(it);
                        break;  //Stop the loop
                    }
                }
            }
        }

    }
    mWindows["Assets"] = { ImGui::GetWindowPos(), ImGui::GetWindowSize() };
    ImGui::End();
}
}