#include <editor/editor.hpp>
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include <algorithm>

namespace Editor {
void
Editor::uiAssets() {

    if (ImGui::Begin("Assets", &mWindowOpen["Assets"], ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Assets");
        for(auto& element : pAssets.Assets){
            ImGui::InputText("##", &element);
        }

        ImGui::InputText("##asset", &mStringInput);
        ImGui::SameLine();
        if (ImGui::Button("Add")) {
            const auto exist = std::find(pAssets.Assets.begin(), pAssets.Assets.end(), mStringInput);
            if(exist == pAssets.Assets.end()) {
                Level::addAsset(mStringInput, pAssets);
                mStringInput.clear();
            }
        }
    }
    mWindows["Assets"] = { ImGui::GetWindowPos(), ImGui::GetWindowSize() };
    ImGui::End();
}
}