#pragma once
#include <SDL.h>
#include <functional>
#include <list>
#include <vector>
#include <utility/timer.hpp>

namespace Common {
/**
 * @brief Add a event to watch for
 */
void
addEventWatcher(std::function<bool(SDL_Event*)> handler, std::list<std::function<bool(SDL_Event*)>>& list);

/**
 * @brief Add event in queue
 */
void
queueEventHandler(Uint32                                                                  evtype,
                  std::function<bool(SDL_Event*)>                                         handler,
                  std::unordered_map<Uint32, std::list<std::function<bool(SDL_Event*)>>>& list);

void
queueProcessHandler(std::function<void(int)> handler, std::list<std::tuple<std::function<void(int)>, Utility::Timer>>& list);

}