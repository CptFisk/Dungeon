#pragma once
#include <cstdint>
#include <graphics/types/baseTexture.hpp>
#include <graphics/types/drawData.hpp>
#include <items/slots.hpp>

namespace Items {

class Items {
  public:
  protected:
  private:
    Graphics::BaseTexture* mTexture;
    const SlotType         mSlot;
    const int16_t          mId;
};

}