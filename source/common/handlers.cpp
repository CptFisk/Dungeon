#include <common/handlers.hpp>

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

void
queueProcessHandler(std::function<void(int)> handler, std::list<std::tuple<std::function<void(int)>, Utility::Timer>>& list) {
    Utility::Timer timer;
    timer.start();
    list.emplace_back(std::move(handler), timer);
}
}