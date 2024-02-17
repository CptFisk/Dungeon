#pragma once
#include <vector>
#include <functional>
#include <SDL3/SDL.h>
#include <list>

namespace Common{
/**
 * @brief Add a event to watch for
 */
void
addEventWatcher(std::function<bool(SDL_Event*)> handler, std::list<std::function<bool(SDL_Event*)>> &list);


}