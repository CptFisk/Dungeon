#include <editor/editor.hpp>
#include <imgui.h>
#include <string>

namespace Editor {
void
Editor::uiMenu() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New project")) {
                mNewFile           = true;
                mShowHeader        = true;
                delete pLevelHeader; // Clean first
                pLevelHeader = new Level::typeHeader{};
                pAssets      = new Level::typeAssets{};
            }
            if (ImGui::MenuItem("Load project")) {
            }
            if (ImGui::MenuItem("Save project")) {
                Level::typeLevelData map = { *pLevelHeader, *pAssets, pTile };

                Level::writeLevelDataToFile(std::string(pLevelHeader->MapName) + ".map", map);
            }

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Project", mMapLoaded)) {
            if (ImGui::MenuItem("Level settings")) {
                mShowHeader = true;
            }
            if (ImGui::MenuItem("Assets")) {
                mShowAssets = true;
            }
            ImGui::EndMenu();
        }
    }

    ImGui::EndMainMenuBar();
}
}
