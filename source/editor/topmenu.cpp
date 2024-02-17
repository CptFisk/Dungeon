#include <editor/editor.hpp>
#include <imgui.h>

namespace Editor {
void
Editor::uiMenu() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New project")) {
            }
            if (ImGui::MenuItem("Load project")) {
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
