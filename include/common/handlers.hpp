#pragma once
#include <SDL3/SDL.h>
#include <functional>
#include <list>
#include <vector>

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

}