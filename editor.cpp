#define SDL_MAIN_HANDLED
#include <editor/editor.hpp>
#include <imgui.h>

int
main() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    Editor::Editor editor(1280, 1024);
    editor.startup();
    editor.getActionManager().registerMouseAction("Click", SDL_BUTTON_LEFT);
    editor.getActionManager().registerKeyboardAction("CameraNorth", SDLK_w);
    editor.getActionManager().registerKeyboardAction("CameraEast", SDLK_d);
    editor.getActionManager().registerKeyboardAction("CameraSouth", SDLK_s);
    editor.getActionManager().registerKeyboardAction("CameraWest", SDLK_a);

    Common::queueProcessHandler(
      [&](Uint32) {
          if (editor.getActionManager().isActionPressed("CameraNorth")) {
              editor.move(Directions::NORTH);
          }
      },
      editor.getProcessing());
    Common::queueProcessHandler(
      [&](Uint32) {
          if (editor.getActionManager().isActionPressed("CameraEast")) {
              editor.move(Directions::EAST);
          }
      },
      editor.getProcessing());
    Common::queueProcessHandler(
      [&](Uint32) {
          if (editor.getActionManager().isActionPressed("CameraSouth")) {
              editor.move(Directions::SOUTH);
          }
      },
      editor.getProcessing());
    Common::queueProcessHandler(
      [&](Uint32) {
          if (editor.getActionManager().isActionPressed("CameraWest")) {
              editor.move(Directions::WEST);
          }
      },
      editor.getProcessing());

    Common::queueEventHandler(
      SDL_QUIT,
      [&](SDL_Event*) {
          editor.terminate();
          return true;
      },
      editor.getEvents());

    Common::queueProcessHandler(
      [&](Uint32) {
          if (editor.getActionManager().isActionRising("Click")) {
              editor.click();
          }
      },
      editor.getProcessing());
    editor.mainLoop();

    return 0;
}