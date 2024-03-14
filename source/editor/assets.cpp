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
            ImGui::InputText("##", &element);
        }

        ImGui::InputText("##asset", &mStringInput);
        ImGui::SameLine();
        if (ImGui::Button("Add")) {
            const auto exist = std::find(fileAssets.Assets.begin(), fileAssets.Assets.end(), mStringInput);
            if(exist == fileAssets.Assets.end()) {
                Level::File::addAsset(mStringInput, fileAssets);
                mStringInput.clear();
            }
        }
    }
    mWindows["Assets"] = { ImGui::GetWindowPos(), ImGui::GetWindowSize() };
    ImGui::End();
}
}