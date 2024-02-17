#include <common/imgui.hpp>
#include <common/sdl.hpp>
#include <editor/editor.hpp>

namespace Editor {
Editor::Editor()
  : mInitHandler(std::make_unique<Common::InitHandler>())
  , pWindow(nullptr)
  , pRenderer(nullptr) {}

Editor::~Editor() {
    mInitHandler->shutdown();
}

Common::ActionManager&
Editor::getActionManager() {
    return *mActionManager;
}

void
Editor::startup() {
    mInitHandler->addInitializer(std::make_shared<Common::SDLInitializer>(&pWindow, &pRenderer));
    mInitHandler->addInitializer(std::make_shared<Common::ImGuiInitializer>(&pWindow, &pRenderer));
    mInitHandler->startup();

    addEventWatcher([&](SDL_Event* evt) { return mActionManager->eventHandler(evt); });
}

}