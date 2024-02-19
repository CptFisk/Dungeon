#include <editor/editor.hpp>
#include <imgui.h>

int
main() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    Editor::Editor editor;
    editor.getActionManager().registerMouseAction("Click", SDL_BUTTON_LEFT);

    Common::queueEventHandler(
      SDL_EVENT_QUIT,
      [&](SDL_Event*) {
          editor.terminate();
          return true;
      },
      editor.getEvents());

    Common::queueProcessHandler(
      [&](Uint32) {
          if (editor.getActionManager().isActionRising("Click")) {
              float mouseX, mouseY;
              SDL_GetMouseState(&mouseX, &mouseY);
              editor.click(mouseX, mouseY);
          }
      },
      editor.getProcessing());

    editor.startup();
    editor.mainLoop();

    return 0;
}