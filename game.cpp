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
    engine.getActionManager().registerKeyboardAction("PlayerNorth", SDLK_w);
    engine.getActionManager().registerKeyboardAction("PlayerEast", SDLK_d);
    engine.getActionManager().registerKeyboardAction("PlayerSouth", SDLK_s);
    engine.getActionManager().registerKeyboardAction("PlayerWest", SDLK_a);
    engine.getActionManager().registerKeyboardAction("Interact", SDLK_SPACE);
    engine.getActionManager().registerKeyboardAction("Exit", SDLK_ESCAPE);
    engine.getActionManager().registerMouseAction("Click", SDL_BUTTON_LEFT);

    Common::queueProcessHandler(
      [&](Uint32) {
          if (engine.getActionManager().isActionRising("Exit")) {
              engine.terminate();
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
          if (engine.getActionManager().isActionPressed("PlayerNorth")) {
              engine.movePlayer(North);
          }
      },
      engine.getProcessing());

    Common::queueProcessHandler(
      [&](Uint32) {
          if (engine.getActionManager().isActionPressed("PlayerEast")) {
              engine.movePlayer(East);
          }
      },
      engine.getProcessing());

    Common::queueProcessHandler(
      [&](Uint32) {
          if (engine.getActionManager().isActionPressed("PlayerSouth")) {
              engine.movePlayer(South);
          }
      },
      engine.getProcessing());

    Common::queueProcessHandler(
      [&](Uint32) {
          if (engine.getActionManager().isActionPressed("PlayerWest")) {
              engine.movePlayer(West);
          }
      },
      engine.getProcessing());

    Common::queueProcessHandler(
      [&](Uint32) {
          if (!engine.getActionManager().isActionPressed("PlayerNorth") && !engine.getActionManager().isActionPressed("PlayerEast") &&
              !engine.getActionManager().isActionPressed("PlayerSouth") && !engine.getActionManager().isActionPressed("PlayerWest")) {
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
