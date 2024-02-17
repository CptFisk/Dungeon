#include <editor/editor.hpp>
#include <imgui.h>
#include <utility/file.hpp>

namespace Editor {
void
Editor::uiMenu() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New project")) {
            }
            if (ImGui::MenuItem("Load project")) {
            }
            if(ImGui::MenuItem("Save project")){
                Utility::writeStructToFile(&mLevelHeader, sizeof(mLevelHeader), std::string(mLevelHeader.MapName) + ".map");
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Project", mMapLoaded)) {
            if(ImGui::MenuItem("Level settings")){
                mShowProjectHeader = true;
            }
            ImGui::EndMenu();
        }
    }

    ImGui::EndMainMenuBar();
}
}
