#include <editor/editor.hpp>
#include <imgui.h>

int
main() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    Editor::Editor editor;
    editor.getActionManager().registerMouseAction("Click", SDL_BUTTON_LEFT);
    editor.getActionManager().registerKeyboardAction("CameraNorth", SDLK_w);
    editor.getActionManager().registerKeyboardAction("CameraEast", SDLK_d);
    editor.getActionManager().registerKeyboardAction("CameraSouth", SDLK_s);
    editor.getActionManager().registerKeyboardAction("CameraWest", SDLK_a);

    Common::queueProcessHandler(
      [&](Uint32) {
          if (editor.getActionManager().isActionPressed("CameraNorth")) {
              ;
          }
      },
      editor.getProcessing());
    Common::queueProcessHandler(
      [&](Uint32) {
          if (editor.getActionManager().isActionPressed("CameraEast")) {
              ;
          }
      },
      editor.getProcessing());
    Common::queueProcessHandler(
      [&](Uint32) {
          if (editor.getActionManager().isActionPressed("CameraSouth")) {
              ;
          }
      },
      editor.getProcessing());
    Common::queueProcessHandler(
      [&](Uint32) {
          if (editor.getActionManager().isActionPressed("CameraWest")) {
              ;
          }
      },
      editor.getProcessing());


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