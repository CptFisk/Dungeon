#include <editor/editor.hpp>
#include <imgui.h>

namespace Editor{

void
Editor::uiProjectHeader() {
    static float color[4];
    static int version;
    ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoAlpha;
    if(!mShowProjectHeader)
        return;
    if(ImGui::Begin("Level settings", &mShowProjectHeader, ImGuiWindowFlags_AlwaysAutoResize)){
        ImGui::InputInt("Header version", &version);
        ImGui::InputText("Level name", mLevelHeader.MapName, IM_ARRAYSIZE(mLevelHeader.MapName));
        ImGui::ColorPicker4("MyColor##4", (float*)&color, flags, nullptr);
        ImGui::End();
    }
    mLevelHeader.BackgroundRed = static_cast<float>(color[0] * 255.0f);
    mLevelHeader.BackgroundGreen = static_cast<float>(color[1] * 255.0f);
    mLevelHeader.BackgroundBlue = static_cast<float>(color[2] * 255.0f);


    if (version >= 0 && version <= UINT8_MAX)
        mLevelHeader.HeaderVersion = static_cast<uint8_t>(version);
}

}