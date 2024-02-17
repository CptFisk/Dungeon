#include <engine/engine.hpp>
#include <iostream>
#include <imgui.h>
#include <common/handlers.hpp>

int
main() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    Engine::Engine engine;
    engine.getActionManager().registerKeyboardAction("PlayerNorth", SDLK_w);
    engine.getActionManager().registerKeyboardAction("PlayerEast", SDLK_d);
    engine.getActionManager().registerKeyboardAction("PlayerSouth", SDLK_s);
    engine.getActionManager().registerKeyboardAction("PlayerWest", SDLK_a);
    engine.getActionManager().registerMouseAction("Click", SDL_BUTTON_LEFT);

    engine.queueProcessHandler([&](Uint32) {
        if (engine.getActionManager().isActionPressed("PlayerNorth")) {
            engine.movePlayer(North);
        }
    });
    engine.queueProcessHandler([&](Uint32) {
        if (engine.getActionManager().isActionPressed("PlayerEast")) {
            engine.movePlayer(East);
        }
    });
    engine.queueProcessHandler([&](Uint32) {
        if (engine.getActionManager().isActionPressed("PlayerSouth")) {
            engine.movePlayer(South);
        }
    });
    engine.queueProcessHandler([&](Uint32) {
        if (engine.getActionManager().isActionPressed("PlayerWest")) {
            engine.movePlayer(West);
        }
    });
    engine.queueProcessHandler([&](Uint32) {
        if (!engine.getActionManager().isActionPressed("PlayerNorth") &&
            !engine.getActionManager().isActionPressed("PlayerEast") &&
            !engine.getActionManager().isActionPressed("PlayerSouth") &&
            !engine.getActionManager().isActionPressed("PlayerWest")) {
            engine.setPlayerAction(Objects::ObjectAction::IDLE);
        }
    });

    engine.queueProcessHandler([&](Uint32) {
        if (engine.getActionManager().isActionRising("Click")) {
            float mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            engine.click(mouseX, mouseY);
        }
    });

    Common::queueEventHandler(SDL_EVENT_QUIT,[&](SDL_Event*) {
        engine.terminate();
        return true;
    },engine.getEvents());

    engine.startup();
    try {
        engine.mainLoop();
    } catch (const std::exception& e) {
        std::cerr << e.what();
    }
    return 0;
}
