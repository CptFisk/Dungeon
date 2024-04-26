#include <algorithm>
#include <editor/editor.hpp>
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

namespace Editor {
void
Editor::uiAssets() {

    if (ImGui::Begin("Assets", &mWindowOpen["Assets"], ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Assets");
        for (auto& element : fileAssets.Assets) {
            ImGui::InputText("##", &element, ImGuiInputTextFlags_ReadOnly);
            ImGui::SameLine();
            if (ImGui::Button(("Delete##" + element).c_str())) {
                Level::File::removeAsset(element, fileAssets,fileTiles);
            }
        }
    }
    mWindows["Assets"] = { ImGui::GetWindowPos(), ImGui::GetWindowSize() };
    ImGui::End();
}
}