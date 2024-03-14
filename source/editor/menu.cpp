#include <editor/editor.hpp>
#include <imgui.h>
#include <string>

namespace Editor {
void
Editor::uiMenu() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New project")) {
                delete fileHeader; // Clean first
                fileHeader                = new Level::File::typeHeader{};
                fileHeader->Level.SizeX   = 16;
                fileHeader->Level.SizeY   = 12;
                fileHeader->HeaderVersion = 1;
                fileAssets.Assets.clear();   //Clear the vector, we start blank
                displayElement("Header");
            }
            if (ImGui::MenuItem("Load project")) {
            }
            if (ImGui::MenuItem("Save project")) {
                fileHeader->Level.Elements = mLevelCoords.size();
                //Level::typeLevelData map = { *pLevelHeader, pAssets, pTile };

                //Level::writeLevelDataToFile(std::string(pLevelHeader->MapName) + ".map", map);
            }

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Project", mMapLoaded)) {
            if (ImGui::MenuItem("Level settings")) {
                displayElement("Header");
            }
            if (ImGui::MenuItem("Assets")) {
                displayElement("Assets");
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Display")) {
            if (ImGui::MenuItem("Grid"))
                displayElement("Grid");
            if (ImGui::MenuItem("Mouse"))
                displayElement("Mouse");
            if(ImGui::MenuItem("Textures"))
                displayElement("Textures");
            ImGui::EndMenu();
        }
        auto status = "Used: " + std::to_string(mLevelCoords.size());
        ImGui::SameLine(ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize(status.c_str()).x);
        ImGui::Text(status.c_str());
        mWindows["TopMenu"] = { ImGui::GetWindowPos(), ImGui::GetWindowSize() };
        ImGui::EndMainMenuBar();

    }
}
}
