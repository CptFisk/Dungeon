#include <editor/editor.hpp>
#include <misc/cpp/imgui_stdlib.h>

namespace Editor {

void
Editor::uiFunctions(typeWindowCovering& area, bool& open, std::vector<std::string>& elements, const std::string& title) {
    if (ImGui::Begin(title.c_str(), &open, ImGuiWindowFlags_AlwaysAutoResize)) {
        static std::string functionName;
        ImGui::InputText("Function name", &functionName, ImGuiInputTextFlags_CharsNoBlank);
        if(ImGui::Button("Add")){
            elements.push_back(functionName);
            functionName = {};
        }
        ImGui::Separator();

        int pos = 0;
        for (auto& element : elements) {
            ImGui::InputText("##", &element, ImGuiInputTextFlags_ReadOnly);

            ImGui::SameLine();
            if (ImGui::Button(("Delete##" + element).c_str())) {
                // Save the name, since it will be cleared
                const auto name = element;
                // Remove element from vector
                elements.erase(std::remove_if(elements.begin(), elements.end(), [name](const std::string a) { return a == name; }),
                              elements.end());
            }
            pos++;
        }
        area = { ImGui::GetWindowPos(), ImGui::GetWindowSize() };
        ImGui::End();
    }

    if (!open)
        hideElement(title);
}
}