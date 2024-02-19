#include <editor/editor.hpp>
#include <imgui.h>
#include <utility/file.hpp>

namespace Editor {
void
Editor::uiMenu() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New project")) {
                mShowProjectHeader = true;
                mNewFile           = true;

                delete pLevelHeader; // Clean first
                pLevelHeader = new Level::LevelHeader{};
                pMapMeta     = new Level::MapMeta{};
            }
            if (ImGui::MenuItem("Load project")) {
            }
            if (ImGui::MenuItem("Save project")) {
                Level::Map map = {*pLevelHeader, *pMapMeta, pTile};

                Level::writeMapToFile("Hello.bin", map);
            }

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Project", mMapLoaded)) {
            if (ImGui::MenuItem("Level settings")) {
                mShowProjectHeader = true;
            }
            ImGui::EndMenu();
        }
    }

    ImGui::EndMainMenuBar();
}
}
