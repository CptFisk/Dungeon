#include <editor/editor.hpp>
#include <imgui.h>

int
main() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    Editor::Editor editor;

    Common::queueEventHandler(
      SDL_EVENT_QUIT,
      [&](SDL_Event*) {
          editor.terminate();
          return true;
      },
      editor.getEvents());

    editor.startup();
    editor.mainLoop();

    return 0;
}