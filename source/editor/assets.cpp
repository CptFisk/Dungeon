#include <editor/editor.hpp>
#include <imgui.h>

namespace Editor {
void
Editor::uiAssets() {
    if (pAssets == nullptr)
        return;
    static char asset[31];
    if (ImGui::Begin("Assets", &mWindowOpen["Assets"], ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Assets");
        for (int i = 0; i < Level::MAX_ASSETS; i++) {
            if (strlen(pAssets->Data[i].Asset) != 0) {
                ImGui::InputText("##", pAssets->Data[i].Asset, IM_ARRAYSIZE(pAssets->Data[i].Asset));
                ImGui::SameLine();
                if (ImGui::Button(("Delete##" + std::to_string(i)).c_str())) {
                    Level::removeAsset(i, pAssets);
                }
            }
        }
        ImGui::InputText("##asset", asset, IM_ARRAYSIZE(asset));
        ImGui::SameLine();
        if (ImGui::Button("Add")) {
            Level::addAsset(asset, pAssets);
            strncpy(asset, "", sizeof(asset)); // Clearing
        }
    }
    mWindows["Assets"] = { ImGui::GetWindowPos(), ImGui::GetWindowSize() };
    ImGui::End();
}
}