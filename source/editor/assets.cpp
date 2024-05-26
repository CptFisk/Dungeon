#include <algorithm>
#include <editor/editor.hpp>
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include <graphics/graphics.hpp>

namespace Editor {
void
Editor::uiAssets() {

    if (ImGui::Begin("Assets", &mWindowOpen["Assets"], ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Assets");
        for (auto& element : fileAssets.Assets) {
            ImGui::InputText("##", &element, ImGuiInputTextFlags_ReadOnly);
            ImGui::SameLine();
            if (ImGui::Button(("Delete##" + element).c_str())) {
                const auto name = element;  //We need to store it, since it will be removed
                if(Level::File::removeAsset(name, fileAssets,fileTiles))
                    removeSpecificTexture(name);
            }
        }
        ImGui::End();
    }
    mWindows["Assets"] = { ImGui::GetWindowPos(), ImGui::GetWindowSize() };

}
}