#include <common/actionmgr.hpp>
#include <global.hpp>

namespace Common {

ActionManager::ActionManager(SDL_Renderer*& renderer, Common::typeScale& scale, float& offsetX, float& offsetY)
  : pRenderer(renderer)
  , mScale(scale)
  , mOffsetX(offsetX)
  , mOffsetY(offsetY)
  , mMouseX{}
  , mMouseY{} {}

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
            mMouseX = event->motion.x;
            mMouseY = event->motion.y;
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
    return SDL_Point{ INT(FLOAT(mMouseX) / mScale.selectedScale), INT(FLOAT(mMouseY) / mScale.selectedScale) };
}

int
ActionManager::getMouseAbsoluteX() const {
    return INT(FLOAT(mMouseX) / mScale.selectedScale);
}

int
ActionManager::getMouseAbsoluteY() const {
    return INT(FLOAT(mMouseY) / mScale.selectedScale);
}

SDL_Point
ActionManager::getMouseRelative() const {
    return SDL_Point{ INT(FLOAT(mMouseX) / mScale.selectedScale) + std::abs(INT(mOffsetX)),
                      INT(FLOAT(mMouseY) / mScale.selectedScale) + std::abs(INT(mOffsetY)) };
}

int
ActionManager::getMouseRelativeX() const {
    return INT(FLOAT(mMouseX) / mScale.selectedScale) + std::abs(INT(mOffsetX));
}

int
ActionManager::getMouseRelativeY() const {
    return INT(FLOAT(mMouseY) / mScale.selectedScale) + std::abs(INT(mOffsetY));
}

}