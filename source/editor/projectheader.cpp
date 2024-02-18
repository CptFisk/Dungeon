#include <editor/editor.hpp>
#include <imgui.h>

namespace Editor{

void
Editor::uiProjectHeader() {
    static float color[4];
    static int version;
    static int mapX;
    static int mapY;
    ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoAlpha;
    if(!mShowProjectHeader || mLevelHeader == nullptr)
        return;
    if(ImGui::Begin("Level settings", &mShowProjectHeader, ImGuiWindowFlags_AlwaysAutoResize)){
        ImGui::InputInt("Header version", &version);
        ImGui::InputInt("Map size X", &mapX);
        ImGui::InputInt("Map size Y", &mapY);
        ImGui::InputText("Level name", mLevelHeader->MapName, IM_ARRAYSIZE(mLevelHeader->MapName));
        ImGui::ColorPicker4("MyColor##4", (float*)&color, flags, nullptr);


        if(ImGui::Button(mNewFile ? "Create" : "Save")){
                mShowProjectHeader = false;
                mMapLoaded = true;

                mLevelHeader->BackgroundRed = static_cast<float>(color[0] * 255.0f);
                mLevelHeader->BackgroundGreen = static_cast<float>(color[1] * 255.0f);
                mLevelHeader->BackgroundBlue = static_cast<float>(color[2] * 255.0f);

                mLevelHeader->HeaderVersion = static_cast<uint8_t>(version);
                mLevelHeader->MapSizeX = static_cast<uint8_t>(mapX);
                mLevelHeader->MapSizeY = static_cast<uint8_t>(mapY);
        }
        ImGui::End();
    }

}

}