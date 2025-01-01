#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <common/handlers.hpp>
#include <engine/engine.hpp>
#include <imgui.h>
#include <iostream>

Engine::Engine engine;

int
main(int argc, char* argv[]) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    engine.startup();
    engine.getActionManager().registerKeyboardAction("PlayerForward", SDLK_w);
    engine.getActionManager().registerKeyboardAction("PlayerRight", SDLK_d);
    engine.getActionManager().registerKeyboardAction("PlayerBackward", SDLK_s);
    engine.getActionManager().registerKeyboardAction("PlayerLeft", SDLK_a);
    engine.getActionManager().registerKeyboardAction("Inventory", SDLK_e);
    engine.getActionManager().registerKeyboardAction("Interact", SDLK_SPACE);
    engine.getActionManager().registerKeyboardAction("Back", SDLK_ESCAPE);
    engine.getActionManager().registerMouseAction("Click", SDL_BUTTON_LEFT);

    Common::queueProcessHandler(
      [&](Uint32) {
          if (engine.getActionManager().isActionRising("Back")) {
              engine.back();
          }
      },
      engine.getProcessing());

    Common::queueProcessHandler(
      [&](Uint32) {
          if (engine.getActionManager().isActionRising("Interact")) {
              engine.interact();
          }
      },
      engine.getProcessing());

    Common::queueProcessHandler(
      [&](Uint32) {
          if (engine.getActionManager().isActionRising("Inventory")) {
              engine.inventory();
          }
      },
      engine.getProcessing());

    Common::queueProcessHandler(
      [&](Uint32) {
          if (engine.getActionManager().isActionPressed("PlayerForward")) {
              engine.movePlayer(Forward);
          }
      },
      engine.getProcessing());

    Common::queueProcessHandler(
      [&](Uint32) {
          if (engine.getActionManager().isActionPressed("PlayerRight")) {
              engine.movePlayer(Right);
          }
      },
      engine.getProcessing());

    Common::queueProcessHandler(
      [&](Uint32) {
          if (engine.getActionManager().isActionPressed("PlayerBackward")) {
              engine.movePlayer(Backward);
          }
      },
      engine.getProcessing());

    Common::queueProcessHandler(
      [&](Uint32) {
          if (engine.getActionManager().isActionPressed("PlayerLeft")) {
              engine.movePlayer(Left);
          }
      },
      engine.getProcessing());

    Common::queueProcessHandler(
      [&](Uint32) {
          if (!engine.getActionManager().isActionPressed("PlayerForward") && !engine.getActionManager().isActionPressed("PlayerRight") &&
              !engine.getActionManager().isActionPressed("PlayerBackward") && !engine.getActionManager().isActionPressed("PlayerLeft")) {
              engine.setPlayerAction(Objects::State::IDLE);
              engine.resetPlayerMomentum();
          }
      },
      engine.getProcessing());

    Common::queueProcessHandler(
      [&](Uint32) {
          if (engine.getActionManager().isActionRising("Click")) {
              engine.click();
          }
      },
      engine.getProcessing());

    Common::queueEventHandler(
      SDL_QUIT,
      [&](SDL_Event*) {
          engine.terminate();
          return true;
      },
      engine.getEvents());

    try {
        engine.mainLoop();
    } catch (const std::exception& e) {
        std::cerr << e.what();
    }
    return 0;
}
