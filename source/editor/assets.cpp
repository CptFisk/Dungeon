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
        for (int i = 0; i < 30 && pAssets->Data[i].Id != 0; i++) {
            ImGui::PushItemWidth(ImGui::CalcTextSize("FF").x + ImGui::GetStyle().ItemSpacing.x * 2.0f);
            ImGui::InputScalar("##uint8", ImGuiDataType_U8, &pAssets->Data[i].Id);
            ImGui::SameLine();
            ImGui::PopItemWidth();
            ImGui::InputText("##", pAssets->Data[i].Asset, IM_ARRAYSIZE(pAssets->Data[i].Asset));
            ImGui::SameLine();
            if (ImGui::Button(("Delete##" + std::to_string(i)).c_str())) {
                Level::removeAsset(pAssets->Data[i].Id, pAssets);
            }
        }
        ImGui::InputText("##asset", asset, IM_ARRAYSIZE(asset));
        ImGui::SameLine();
        if (ImGui::Button("Add")) {
            Level::addAsset(asset, pAssets);
            strncpy(asset, "", sizeof(asset)); // Clearing
        }
    }
    ImGui::End();
}
}