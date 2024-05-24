#pragma once
#include <SDL.h>
#include <common/structures.hpp>
#include <graphics/animatedTexture.hpp>
#include <graphics/types/simpleTexture.hpp>
#include <mutex>
#include <thread>

namespace Objects {

/**
 * @brief Base class for a door. The class handles 2 animation and swap between them with the help of a thread.
 * @brief The class is thread-safe
 */
class Door {
  public:
    Door(const SDL_FRect&             position,
         Graphics::AnimatedTexture*   opening,
         Graphics::AnimatedTexture*   closing,
         bool                         open = false);
    ~Door();

    [[nodiscard]] Common::typeDrawData& getDrawData();
    void                                interact(bool condition);

  protected:
    void setOpenGraphic();
    void setClosedGraphic();

  private:
    bool                        mOpen; // State of door (false = closed, true = open)
    Graphics::AnimatedTexture*  mAnimationOpening;
    Graphics::AnimatedTexture*  mAnimationClosing;

    Common::typeDrawData mDrawData; // Used for returning the graphic
    SDL_FRect            mPosition;

    std::mutex           mtx;
    std::thread          mThread; // Used to swap state after animation finish
};
}