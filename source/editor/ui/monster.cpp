#include <editor/editor.hpp>
#include <monster/definition.hpp>
namespace Editor {

void
Editor::uiMonster(Editor::Editor::typeWindowCovering& area, bool& open) {
    if (ImGui::Begin("Monster", &open, ImGuiWindowFlags_AlwaysAutoResize)) {
        static int currentItem = mSelectedMonster; // Selector

        if (ImGui::BeginListBox("##Monster")) {
            for (auto i = 1; i < Monster::monsters.size(); i++) {
                const bool selected = (currentItem == i);
                if (ImGui::Selectable(Monster::monsters[i].Name.c_str(), selected)) {
                    currentItem = i;
                    mSelectedMonster = i;
                }
                if (selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndListBox();
        }
        area = { ImGui::GetWindowPos(), ImGui::GetWindowSize() };
        ImGui::End();
    }

    if (!open)
        hideElement("Monster");
}

}