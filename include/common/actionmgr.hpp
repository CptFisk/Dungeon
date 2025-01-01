#pragma once
#include <SDL2/SDL.h>
#include <common/scale.hpp>
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace Common {
class ActionManager {
  public:
    ActionManager(SDL_Renderer*& renderer, Common::typeScale& scale, float& offsetX, float& offsetY);

    /**
     * @brief Bind a renderer to the action manager
     * @param renderer
     */
    void registerKeyboardAction(const std::string& name, SDL_Keycode key);
    void registerMouseAction(const std::string& name, Uint8 button);

    [[maybe_unused]] [[nodiscard]] bool isActionPressed(const std::string& name);
    [[maybe_unused]] [[nodiscard]] bool isActionReleased(const std::string& name);

    [[maybe_unused]] [[nodiscard]] bool isActionRising(const std::string& name);
    [[maybe_unused]] [[nodiscard]] bool isActionFalling(const std::string& name);

    [[maybe_unused]] [[nodiscard]] bool eventHandler(SDL_Event* event);

    [[maybe_unused]] [[nodiscard]] SDL_Point getMouseAbsolute() const;
    [[maybe_unused]] [[nodiscard]] int       getMouseAbsoluteX() const;
    [[maybe_unused]] [[nodiscard]] int       getMouseAbsoluteY() const;
    [[maybe_unused]] [[nodiscard]] SDL_Point getMouseRelative() const;
    [[maybe_unused]] [[nodiscard]] int       getMouseRelativeX() const;
    [[maybe_unused]] [[nodiscard]] int       getMouseRelativeY() const;

  protected:
  private:
    float&                             mOffsetX;  // Offset from perspective
    float&                             mOffsetY;  // Offset from perspective
    int                                mMouseX;   // Mouse X position
    int                                mMouseY;   // Mouse Y position
    std::map<std::string, SDL_Keycode> mKeyboard; // Key bindings
    std::map<std::string, Uint8>       mMouse;    // Mouse binding

    std::map<std::string, bool> mActive;
    std::map<std::string, bool> mRising;
    std::map<std::string, bool> mFalling;

    SDL_Renderer*&     pRenderer;
    Common::typeScale& mScale;
};
}