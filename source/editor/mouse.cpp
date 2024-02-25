#include <editor/editor.hpp>
#include <imgui.h>

#define BUTTON_COLOR(STATE, TEXT)                                                     \
    do {                                                                              \
        if (mMouse == STATE) {                                                        \
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.8f, 0.4f, 1.0f }); \
        } else {                                                                      \
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.8f, 0.8f, 1.0f }); \
        }                                                                             \
        if (ImGui::Button(#TEXT, buttonSize))                                         \
            mMouse = STATE;                                                           \
        ImGui::PopStyleColor(1);                                                      \
    } while (false);

namespace Editor {
void
Editor::uiMouse() {
    ImGui::ShowDemoWindow();
    if (ImGui::Begin("Mouse", &mWindowOpen["Mouse"], ImGuiWindowFlags_AlwaysAutoResize)) {

        ImVec2 buttonSize(ImGui::GetContentRegionAvail().x, 0);
        ImGui::SeparatorText("Graphical");
        BUTTON_COLOR(DEFAULT, None)
        BUTTON_COLOR(REMOVE, Remove)

        ImGui::SeparatorText("Tiletype");
        BUTTON_COLOR(TEXTURE, Texture)
        BUTTON_COLOR(OBSTACLE, Obstacle)
        mWindows["Mouse"] = { ImGui::GetWindowPos(), ImGui::GetWindowSize() };
        ImGui::End();
    }
}
}