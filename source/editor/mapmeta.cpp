#include <editor/editor.hpp>
#include <imgui.h>
namespace Editor {
void
Editor::uiMapMeta() {
    if (!mShowMapMeta || pMapMeta == nullptr)
        return;

    if (ImGui::Begin("Assets", &mShowProjectHeader, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Assets");
        for (int i = 0; i < 30 && pMapMeta->Data[i].Id != 0; i++) {
            ImGui::PushItemWidth(ImGui::CalcTextSize("FF").x + ImGui::GetStyle().ItemSpacing.x * 2.0f);
            ImGui::InputScalar("##uint8", ImGuiDataType_U8, &pMapMeta->Data[i].Id);
            ImGui::SameLine();
            ImGui::PopItemWidth();
            ImGui::InputText("##", pMapMeta->Data[i].Asset, IM_ARRAYSIZE(pMapMeta->Data[i].Asset));
            ImGui::SameLine();
            if (ImGui::Button(("Delete##" + std::to_string(i)).c_str())){
                Level::deleteMapMeta(pMapMeta->Data[i].Id, pMapMeta);
            }
        }
    }
    ImGui::End();
}
}