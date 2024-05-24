#pragma once
#include <common/structures.hpp>
#include <graphics/animatedTexture.hpp>
#include <graphics/types/simpleTexture.hpp>

namespace Objects {

class Door {
  public:
    Door(const Graphics::typeSimpleTexture& graphic, const Graphics::AnimatedTexture& animatedGraphic, bool open = false);
    ~Door();

    [[nodiscard]] Common::typeDrawData& getDrawData();
    void open(bool condition);
  protected:
  private:
    bool                        mOpen; // State of door (false = closed, true = open)
    Graphics::AnimatedTexture   mAnimatedGraphic;
    Graphics::typeSimpleTexture mGraphic;

    Common::typeDrawData mDrawData; // Used for returning the graphic
};
}