#include <editor/editor.hpp>
#include <graphics/graphics.hpp>
#include <misc/cpp/imgui_stdlib.h>

namespace Editor {

void
Editor::uiTexture(typeWindowCovering&                                                area,
                  bool&                                                              open,
                  const std::vector<std::pair<Graphics::TextureTypes, std::string>>& textures,
                  std::pair<Graphics::TextureTypes, std::string>&                    selectedTexture) {
    if (ImGui::Begin("Textures", &open, ImGuiWindowFlags_AlwaysAutoResize)) {
        static int         currentItem;
        static std::string filter;
        ImGui::InputText("##Filter", &filter);
        if (ImGui::BeginListBox("##Textures")) {
            for (int i = 0; i < textures.size(); i++) {
                if (textures[i].second.find(filter) != std::string::npos) {
                    const bool selected = (currentItem == i);
                    if (ImGui::Selectable(textures[i].second.c_str(), selected)) {
                        currentItem      = i;
                        selectedTexture = textures[i];
                    }
                    if (selected)
                        ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndListBox();
        }
        area = { ImGui::GetWindowPos(), ImGui::GetWindowSize() };
        ImGui::End();
    }

    if (!open)
        hideElement("Textures");
}
}