#pragma once
#include <SDL.h>
#include <graphics/types/animatedTexture.hpp>
#include <graphics/types/drawData.hpp>
#include <mutex>
#include <thread>

namespace Objects {

/**
 * @brief Base class for a door. The class handles 2 animation and swap between them with the help of a thread.
 * @brief The class is thread-safe
 */
class Door {
  public:
    /**
     * @brief Constructor for door
     * @param position The destination in map
     * @param opening Animation for door opening
     * @param closing Animation for door closing
     * @param open Determine the start-state of the door
     */
    Door(const int& x, const int& y, Graphics::AnimatedTexture* opening, Graphics::AnimatedTexture* closing, bool open = false);
    /**
     * @brief De-constructor that wait for the thread to stop
     */
    ~Door();
    /**
     * @brief Returns the draw data that can later be passed to the perspective manager
     */
    [[nodiscard]] Graphics::typeDrawData& getDrawData();
    void                                  interact(bool condition);

    /**
     * @return True if you can walk through the door
     */
    [[nodiscard]] bool isPassable() const;
    /**
     * @return Position of door
     */
    [[nodiscard]] SDL_FRect getPosition() const;

  protected:
  private:
    bool                       mOpen; // State of door (false = closed, true = open)
    Graphics::AnimatedTexture* mAnimationOpening;
    Graphics::AnimatedTexture* mAnimationClosing;

    std::vector<SDL_Rect> mAnimationOpeningViewport; // Viewports
    std::vector<SDL_Rect> mAnimationClosingViewport; // Viewports

    Graphics::typeDrawData mDrawData; // Used for returning the graphic
    SDL_FRect              mPosition;

    std::thread mThread; // Used to swap state after animation finish
};
}