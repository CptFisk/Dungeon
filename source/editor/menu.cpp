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
                pLevelHeader = new Level::Header{};
                pAssets      = new Level::Assets{};
            }
            if (ImGui::MenuItem("Load project")) {
            }
            if (ImGui::MenuItem("Save project")) {
                Level::typeLevel map = { *pLevelHeader, *pAssets, pTile };

                Level::writeLevelToFile(std::string(pLevelHeader->MapName) + ".map", map);
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
