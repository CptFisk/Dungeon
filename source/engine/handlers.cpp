#include <engine/engine.hpp>

namespace Engine {
void
Engine::addEventWatcher(std::function<bool(SDL_Event*)> handler) {
    mEventWatcher.push_back(handler);
}

void
Engine::queueEventHandler(Uint32 evenType, std::function<bool(SDL_Event*)> handler) {
    mEvents[evenType].push_back(std::move(handler));
}

void
Engine::queueProcessHandler(std::function<void(int)> handler) {
    Timer timer;
    timer.start();
    mProcessing.emplace_back(std::move(handler), timer);
}
}