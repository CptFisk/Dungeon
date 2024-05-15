#pragma once
#include <SDL3/SDL.h>
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace Common {
class ActionManager {
  public:
    void registerKeyboardAction(const std::string& name, SDL_Keycode key);
    void registerMouseAction(const std::string& name, Uint8 button);

    bool isActionPressed(const std::string& name);
    bool isActionReleased(const std::string& name);

    bool isActionRising(const std::string& name);
    bool isActionFalling(const std::string& name);

    bool eventHandler(SDL_Event* event);

  protected:
  private:
    std::map<std::string, SDL_Keycode> mKeyboard; // Key bindings
    std::map<std::string, Uint8>       mMouse;    // Mouse binding

    std::map<std::string, bool> mActive;
    std::map<std::string, bool> mRising;
    std::map<std::string, bool> mFalling;
};
}