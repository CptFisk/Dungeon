#include <editor/editor.hpp>
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include <algorithm>

namespace Editor {
void
Editor::uiAssets() {

    if (ImGui::Begin("Assets", &mWindowOpen["Assets"], ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Assets");
        for(auto& element : pAssets.Data){
            ImGui::InputText("##", &element.Asset);
        }

        ImGui::InputText("##asset", &mStringInput);
        ImGui::SameLine();
        if (ImGui::Button("Add")) {
            const auto exist = std::any_of(pAssets.Data.begin(), pAssets.Data.end(),
                                 [&](const Level::typeAssetItem& item){
                                     return item.Asset == mStringInput;
                                 });
            if(!exist) {
                pAssets.Data.push_back({ mStringInput });
                mStringInput.clear();
            }
        }
    }
    mWindows["Assets"] = { ImGui::GetWindowPos(), ImGui::GetWindowSize() };
    ImGui::End();
}
}