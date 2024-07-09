#include <algorithm>
#include <editor/editor.hpp>
#include <graphics/graphics.hpp>
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

namespace Editor {

void
Editor::uiAssets(typeWindowCovering& area, bool& open, Level::File::typeAssets& assets) {
    if (ImGui::Begin("Assets", &open, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Assets");
        uint8_t pos = 0;
        for (auto& element : assets.Assets) {
            ImGui::InputText("##", &element, ImGuiInputTextFlags_ReadOnly);
            ImGui::SameLine();
            if (ImGui::Button(("Delete##" + element).c_str())) {
                // Save the name, since it will be cleared
                const auto name = element;
                //Remove element from vector
                assets.Assets.erase(
                  std::remove_if(assets.Assets.begin(), assets.Assets.end(), [name](const std::string a) { return a == name; }),
                  assets.Assets.end());
                removeSpecificTexture(name, editorTiles, pos);
                pos++;
            }
        }
        area = { ImGui::GetWindowPos(), ImGui::GetWindowSize() };
        ImGui::End();
    }
}
}