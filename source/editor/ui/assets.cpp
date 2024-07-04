#include <algorithm>
#include <editor/editor.hpp>
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include <graphics/graphics.hpp>

namespace Editor {

void
Editor::uiAssets(typeWindowCovering& area,bool &open, Level::File::typeAssets& assets) {
    if (ImGui::Begin("Assets", &open, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Assets");
        for (auto& element : assets.Assets) {
            ImGui::InputText("##", &element, ImGuiInputTextFlags_ReadOnly);
            ImGui::SameLine();
            if (ImGui::Button(("Delete##" + element).c_str())) {
                if(Level::File::removeAsset(element, assets))
                    removeSpecificTexture(element, editorTiles);
            }
        }
        area = { ImGui::GetWindowPos(), ImGui::GetWindowSize() };
        ImGui::End();
    }
}
}