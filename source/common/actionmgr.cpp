#include <cmake.hpp>
#include <common/actionmgr.hpp>
#include <global.hpp>

namespace Common {

ActionManager::ActionManager(SDL_Renderer*& renderer, Common::typeScale& scale, float& offsetX, float& offsetY)
  : mouseX(0.0f)
  , mouseY(0.0f)
  , pRenderer(renderer)
  , mScale(scale)
  , mOffsetX(offsetX)
  , mOffsetY(offsetY) {}

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
        case SDL_MOUSEMOTION:
#ifdef GAME_MODE
            mAbsoluteMouse = { INT(FLOAT(event->button.x) / mScale.selectedScale), INT(FLOAT(event->button.y) / mScale.selectedScale) };
            mRelativeMouse = { mAbsoluteMouse.x + INT(mOffsetX), mAbsoluteMouse.y + INT(mOffsetY) };
#endif
#ifdef EDITOR_MODE
            mouseX = event->button.x;
            mouseY = event->button.y;
#endif
            break;
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
                if (key == event->button.button)
                    mActive[name] = true;
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

SDL_Point
ActionManager::getMouseAbsolute() const {
    return mAbsoluteMouse;
}

int
ActionManager::getMouseAbsoluteX() const {
    return mAbsoluteMouse.x;
}

int
ActionManager::getMouseAbsoluteY() const {
    return mAbsoluteMouse.y;
}

SDL_Point
ActionManager::getMouseRelative() const {
    return mRelativeMouse;
}

int
ActionManager::getMouseRelativeX() const {
    return mRelativeMouse.x;
}

int
ActionManager::getMouseRelativeY() const {
    return mRelativeMouse.y;
}

}