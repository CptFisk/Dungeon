#include <editor/editor.hpp>
#include <imgui.h>
namespace Editor {
void
Editor::uiMapMeta() {
    if (!mShowMapMeta || pMapMeta == nullptr)
        return;
    if(ImGui::Begin("Level settings", &mShowProjectHeader, ImGuiWindowFlags_AlwaysAutoResize)){
        ImGui::End();
    }
}
}