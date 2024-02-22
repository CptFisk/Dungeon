#include <editor/editor.hpp>
#include <imgui.h>

#define BUTTON_COLOR(STATE)                                                           \
    do {                                                                              \
        if (mMouse == STATE) {                                                        \
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.8f, 0.4f, 1.0f }); \
        } else {                                                                      \
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.8f, 0.8f, 1.0f }); \
        }                                                                             \
    } while (false);

namespace Editor {
void
Editor::uiMouse() {
    if (ImGui::Begin("Mouse", &mWindowOpen["Mouse"], ImGuiWindowFlags_NoResize)) {

        ImVec2 buttonSize(ImGui::GetContentRegionAvail().x, 0);

        BUTTON_COLOR(DEFAULT)
        if (ImGui::Button("None", buttonSize))
            mMouse = DEFAULT;
        ImGui::PopStyleColor(1);

        BUTTON_COLOR(REMOVE)
        if (ImGui::Button("Remove", buttonSize))
            mMouse = REMOVE;
        ImGui::PopStyleColor(1);

        BUTTON_COLOR(BACKGROUND)
        if (ImGui::Button("Background", buttonSize))
            mMouse = BACKGROUND;
        ImGui::PopStyleColor(1);

        ImGui::End();
    }
}
}