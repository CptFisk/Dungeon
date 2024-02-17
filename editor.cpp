#include <editor/editor.hpp>
#include <imgui.h>

int
main() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    Editor::Editor editor;
    editor.startup();

    return 0;
}