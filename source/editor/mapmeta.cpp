#include <editor/editor.hpp>
#include <imgui.h>
namespace Editor {
void
Editor::uiMapMeta() {
    if (!mShowMapMeta || pMapMeta == nullptr)
        return;
    pMapMeta->Data[0].Id = 2;
    pMapMeta->Data[1].Id = 7;
    if (ImGui::Begin("Level settings", &mShowProjectHeader, ImGuiWindowFlags_AlwaysAutoResize)) {
        for (int i = 0; i < 30 && pMapMeta->Data[i].Id != 0; i++) {
            ImGui::PushItemWidth(ImGui::CalcTextSize("FF").x + ImGui::GetStyle().ItemSpacing.x * 2.0f);
            ImGui::InputScalar("##uint8", ImGuiDataType_U8, &pMapMeta->Data[i].Id);
            ImGui::SameLine();
            ImGui::PopItemWidth();
            ImGui::InputText("##", pMapMeta->Data[i].Asset, IM_ARRAYSIZE(pMapMeta->Data[i].Asset));
        }
        ImGui::End();
    }
}
}