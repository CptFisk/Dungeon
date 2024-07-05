#include <editor/editor.hpp>
#include <imgui.h>
#include <string>

namespace Editor {
void
Editor::uiMenu() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New project")) {
                fileHeader = Level::File::typeHeaderData{};
                fileAssets.Assets.clear(); // Clear the vector, we start blank
                displayElement("Header");
            }
            if (ImGui::BeginMenu("Load project")) {
                for (const auto& file : mMapFiles) {
                    if (ImGui::MenuItem(file.c_str()))
                        loadLevel(Level::File::readLevelData(file));
                }
                ImGui::EndMenu();
            }
            if (ImGui::MenuItem("Save project")) {
                std::vector<int> temp; // Temporary storage
                for (const auto& [asset, value] : animationValues) {
                    temp.push_back(value);
                }
                fileAssets.AnimationValue = Common::findLcm(temp);
                Level::File::typeTiles tiles(editorTiles.size());

                for (int i = 0; i < editorTiles.size(); i++) {
                    tiles.Tiles[i] = editorTiles[i]->getTileData();
                }

                Level::File::typeLevelData map = { fileHeader, fileAssets, tiles, fileDoors, fileWarps, fileSpawns };
                const std::string fileName = UINT8_STRING(fileHeader.Data.X) + UINT8_STRING(fileHeader.Data.Y) + UINT8_STRING(fileHeader.Data.Z);
                Level::File::writeLevelDataToFile("levels/" + fileName + ".map", map);
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
            if (ImGui::MenuItem("Overlay", nullptr, showOverlay))
                showOverlay = !showOverlay;
            if (ImGui::MenuItem("Numbers", nullptr, showNumbers))
                showNumbers = !showNumbers;
            if (ImGui::MenuItem("Grid", nullptr, showGrid))
                showGrid = !showGrid;
            if (ImGui::MenuItem("Mouse"))
                displayElement("Mouse");
            if (ImGui::MenuItem("Textures"))
                displayElement("Textures");
            if (ImGui::MenuItem("Doors"))
                displayElement("Doors");
            if (ImGui::MenuItem("Warps"))
                displayElement("Warps");
            ImGui::EndMenu();
        }
        auto status = "Used: " + std::to_string(mLevelCoords.size());
        auto coords = "\tx: " + std::to_string(clickedCoord.first) + " y: " + std::to_string(clickedCoord.second);

        ImGui::SameLine(ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize((status + coords).c_str()).x);
        ImGui::Text((status + coords).c_str());
        mWindows["TopMenu"] = { ImGui::GetWindowPos(), ImGui::GetWindowSize() };
        ImGui::EndMainMenuBar();
    }
}
}
