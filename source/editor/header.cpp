#include <editor/editor.hpp>
#include <imgui.h>

namespace Editor{

void
Editor::uiHeader() {
    static float color[4];

    ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoAlpha;
    if(!mShowHeader || pLevelHeader == nullptr)
        return;
    if(ImGui::Begin("Level settings", &mShowHeader, ImGuiWindowFlags_AlwaysAutoResize)){
        ImGui::InputScalar("Header version", ImGuiDataType_U8, &pLevelHeader->HeaderVersion);
        ImGui::InputScalar("Map size X", ImGuiDataType_U8, &pLevelHeader->SizeX);
        ImGui::InputScalar("Map size Y", ImGuiDataType_U8, &pLevelHeader->SizeY);
        ImGui::InputText("Level name", pLevelHeader->MapName, IM_ARRAYSIZE(pLevelHeader->MapName));
        ImGui::ColorPicker4("MyColor##4", (float*)&color, flags, nullptr);


        if(ImGui::Button(mNewFile ? "Create" : "Save")){
            mShowHeader  = false;
                mShowAssets = true;
                mNewFile = false;
                mMapLoaded = true;
                pTile = Level::newTileData(pLevelHeader->SizeX, pLevelHeader->SizeY);
                pVisualTile = newVisualTile();  //Generate a new visual tile
                Level::addAsset("PurpleFloor", pAssets);

                pLevelHeader->Color.BackgroundRed = static_cast<float>(color[0] * 255.0f);
                pLevelHeader->Color.BackgroundGreen = static_cast<float>(color[1] * 255.0f);
                pLevelHeader->Color.BackgroundBlue = static_cast<float>(color[2] * 255.0f);

        }

    }
    ImGui::End();

}

}