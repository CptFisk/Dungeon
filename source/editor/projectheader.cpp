#include <editor/editor.hpp>
#include <imgui.h>

namespace Editor{

void
Editor::uiProjectHeader() {
    static float color[4];

    ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoAlpha;
    if(!mShowProjectHeader || pLevelHeader == nullptr)
        return;
    if(ImGui::Begin("Level settings", &mShowProjectHeader, ImGuiWindowFlags_AlwaysAutoResize)){
        ImGui::InputScalar("Header version", ImGuiDataType_U8, &pLevelHeader->HeaderVersion);
        ImGui::InputScalar("Map size X", ImGuiDataType_U8, &pLevelHeader->MapSizeX);
        ImGui::InputScalar("Map size Y", ImGuiDataType_U8, &pLevelHeader->MapSizeY);
        ImGui::InputText("Level name", pLevelHeader->MapName, IM_ARRAYSIZE(pLevelHeader->MapName));
        ImGui::ColorPicker4("MyColor##4", (float*)&color, flags, nullptr);


        if(ImGui::Button(mNewFile ? "Create" : "Save")){
                mShowProjectHeader = false;
                mShowMapMeta = true;
                mNewFile = false;
                mMapLoaded = true;
                for(int i = 0; i < 31;i++){
                    Level::addMapMeta("Hello world",pMapMeta);
                }
                //Clear old map if any
                pTile = Level::newTile(pLevelHeader->MapSizeX, pLevelHeader->MapSizeY);
                const int size = pLevelHeader->MapSizeX * pLevelHeader->MapSizeY;
                for(int i=0; i < size;i++){
                    pTile[i]->Id = 255;
                    pTile[i]->Type = (Level::TileType)0xAA;
                }
                pLevelHeader->BackgroundRed = static_cast<float>(color[0] * 255.0f);
                pLevelHeader->BackgroundGreen = static_cast<float>(color[1] * 255.0f);
                pLevelHeader->BackgroundBlue = static_cast<float>(color[2] * 255.0f);

        }

    }
    ImGui::End();

}

}