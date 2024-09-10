#include <common/actionmgr.hpp>
#include <global.hpp>
#include <cmake.hpp>

namespace Common {

ActionManager::ActionManager(SDL_Renderer*& renderer, Common::typeScale& scale)
  : mouseX(0.0f)
  , mouseY(0.0f)
  , pRenderer(renderer)
  , mScale(scale) {}

void
ActionManager::registerKeyboardAction(const std::string& name, SDL_Keycode key) {
    mKeyboard[name] = key;
}

void
ActionManager::registerMouseAction(const std::string& name, Uint8 button) {
    mMouse[name] = button;
}

bool
ActionManager::eventHandler(SDL_Event* event) {
    switch (event->type) {
        case SDL_KEYDOWN:
            for (auto& [name, key] : mKeyboard) {
                if (key == event->key.keysym.sym)
                    mActive[name] = true;
            }
            break;
        case SDL_KEYUP:
            for (auto& [name, key] : mKeyboard) {
                if (key == event->key.keysym.sym)
                    mActive[name] = false;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            for (auto& [name, key] : mMouse) {
                if (key == event->button.button) {
                    mActive[name] = true;
#ifdef GAME_MODE
                    mouseX        = INT(FLOAT(event->button.x) / mScale.selectedScale);
                    mouseY        = INT(FLOAT(event->button.y) / mScale.selectedScale);
#endif
#ifdef EDITOR_MODE
                    mouseX        = event->button.x;
                    mouseY        = event->button.y;
#endif
                }
            }
            break;
        case SDL_MOUSEBUTTONUP:
            for (auto& [name, key] : mMouse) {
                if (key == event->button.button)
                    mActive[name] = false;
            }
            break;
    }
    return true;
}

bool
ActionManager::isActionPressed(const std::string& name) {
    return mActive[name];
}

bool
ActionManager::isActionReleased(const std::string& name) {
    return mActive[name];
}

bool
ActionManager::isActionRising(const std::string& name) {
    const bool result = mActive[name] && !mRising[name];
    mRising[name]     = mActive[name];
    return result;
}

bool
ActionManager::isActionFalling(const std::string& name) {
    const bool result = !mActive[name] && !mFalling[name];
    mFalling[name]    = !mActive[name];
    return result;
}

}