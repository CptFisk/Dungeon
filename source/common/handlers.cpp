#include <engine/engine.hpp>

namespace Common {
void
addEventWatcher(std::function<bool(SDL_Event*)> handler, std::list<std::function<bool(SDL_Event*)>>& list) {
    list.push_back(handler);
}

void
queueEventHandler(Uint32                                                                  evenType,
                  std::function<bool(SDL_Event*)>                                         handler,
                  std::unordered_map<Uint32, std::list<std::function<bool(SDL_Event*)>>>& list) {
    list[evenType].push_back(std::move(handler));
}

}

namespace Engine {

void
Engine::queueProcessHandler(std::function<void(int)> handler) {
    Utility::Timer timer;
    timer.start();
    mProcessing.emplace_back(std::move(handler), timer);
}
}