#include <editor/editor.hpp>

namespace Editor {

void
Editor::uiUnit(Editor::Editor::typeWindowCovering&                     area,
               bool&                                                   open,
               const std::vector<std::pair<std::string, std::string>>& elements,
               const std::string&                                      element,
               int&                                                    selector) {
    // Generate popup
    if (ImGui::Begin(element.c_str(), &open, ImGuiWindowFlags_AlwaysAutoResize)) {
        static int        currentItem = selector; // Selector
        const std::string label       = "##" + element;
        if (ImGui::BeginListBox(label.c_str())) {
            int pos = 0;
            for (auto& [name, defaultImage] : elements) {
                if (pos != 0) {
                    const bool selected = (currentItem == pos);
                    if (ImGui::Selectable(name.c_str(), selected)) {
                        currentItem = pos;
                        selector    = pos;
                    }
                    if (selected)
                        ImGui::SetItemDefaultFocus();
                }
                pos++;
            }
            ImGui::EndListBox();
        }

        area = { ImGui::GetWindowPos(), ImGui::GetWindowSize() };
        ImGui::End();
    }
    // Close was triggered
    if (!open)
        hideElement(element);
}

}