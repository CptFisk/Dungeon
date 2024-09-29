#include <common/segment.hpp>
#include <editor/editor.hpp>
#include <file/engineFile.hpp>
#include <file/export.hpp>
#include <imgui.h>
#include <string>

std::string
generateFileName(const Common::type3DMapCoordinate& coords, const std::string& extension) {
    return std::string(UINT8_STRING(coords.X) + UINT8_STRING(coords.Y) + UINT8_STRING(coords.Z)) + extension;
}

// Internal function to find LCM for animation values
int
findAnimationValue(const std::unordered_map<std::string, int>& data) {
    std::vector<int> temp;
    for (const auto& [asset, value] : data) {
        if (value > 0)
            temp.emplace_back(value);
    }
    return Common::findLcm(temp);
}

namespace Editor {
void
Editor::uiMenu() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New project")) {
                fileHeader = File::typeHeaderData{};
                fileAssets.Assets.clear(); // Clear the vector, we start blank
                displayElement("Header");
            }
            if (ImGui::BeginMenu("Load project")) {
                for (const auto& file : mMapFiles) {
                    if (ImGui::MenuItem(file.c_str()))
                        loadLevel(File::readEditorFile(file));
                }
                ImGui::EndMenu();
            }
            if (ImGui::MenuItem("Export map", nullptr, nullptr, mMapLoaded)) {
                Common::typeSegment segments;
                const auto          animationBase = findAnimationValue(animationValuesBase);
                const auto          animationTop  = findAnimationValue(animationValuesTop);

                File::typeEditorTiles tiles(editorTiles.size());       // Locally, only used to generate map
                for (int i = 0; i < editorTiles.size(); i++) {
                    tiles.Tiles[i]       = editorTiles[i]->getTileData();
                }
                Common::createMap(pRenderer, mGraphics, segments, animationBase, animationTop, tiles, fileAssets);
                // Constructing filename
                const auto fileName = generateFileName(fileHeader.MapCoordinate, ".lvl");

                File::writeEngineData("levels/" + fileName, pRenderer, fileHeader, segments, tiles);
                Common::clearTypeSegment(segments);
            }
            if (ImGui::MenuItem("Save project")) {

                File::typeEditorTiles tiles(editorTiles.size());
                for (int i = 0; i < editorTiles.size(); i++) {
                    tiles.Tiles[i] = editorTiles[i]->getTileData();
                }

                File::typeEditorFile map = { fileHeader, fileAssets, tiles, fileDoors, fileWarps };

                const auto fileName = generateFileName(fileHeader.MapCoordinate, ".map");
                File::writeEditorFile("levels/" + fileName, map);
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
            if (ImGui::MenuItem("On load")) {
                displayElement("OnLoad");
            }
            if (ImGui::MenuItem("On exit")) {
                displayElement("OnExit");
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
            if (ImGui::MenuItem("Monster"))
                displayElement("Monster");
            if (ImGui::MenuItem("Npc"))
                displayElement("Npc");
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
