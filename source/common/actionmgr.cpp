#include <common/actionmgr.hpp>
#include <iostream>
namespace Common {

void
ActionManager::registerKeyboardAction(const std::string& name, SDL_KeyCode key) {
    mKeyboard[name] = key;
}

void
ActionManager::registerMouseAction(const std::string& name, Uint8 button) {
    mMouse[name] = button;
}

bool
ActionManager::eventHandler(SDL_Event* event) {
    switch (event->type) {
        case SDL_EVENT_KEY_DOWN:
            for (auto& [name, key] : mKeyboard) {
                if (key == event->key.keysym.sym)
                    mActive[name] = true;
            }
            break;
        case SDL_EVENT_KEY_UP:
            for (auto& [name, key] : mKeyboard) {
                if (key == event->key.keysym.sym)
                    mActive[name] = false;
            }
            break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            for (auto& [name, key] : mMouse) {
                if (key == event->button.button)
                    mActive[name] = true;
            }
            break;
        case SDL_EVENT_MOUSE_BUTTON_UP:
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