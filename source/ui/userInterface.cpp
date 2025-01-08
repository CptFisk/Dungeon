#include <ui/userInterface.hpp>
#include <utility/scale.hpp>

namespace Engine::UI {

UserInterface::UserInterface(Common::typeScale&              scale,
                             //Related to inventory
                             std::array<Items::Slot, 30>& slots,
                             Graphics::UserInterfaceTexture* inventory,
                             Graphics::UserInterfaceTexture* selector,
                             //Related to indicators
                             Graphics::UserInterfaceTexture* currentHotkey,
                             Graphics::AnimatedTexture*      red,
                             Graphics::AnimatedTexture*      green,
                             Graphics::AnimatedTexture*      yellow,
                             Graphics::GeneratedTexture*     background,
                             Stats::Stats&                   stats)
  : mScale(scale)
  //Inventory
  , pInventory(inventory)
  ,pSelector(selector)
  , mSlots(slots)
      ,mInventoryDrawData(inventory->getTexture(), nullptr, new SDL_FRect(0.0f, 0.0f, 0.0f, 0.0f))
  //Indicators
  , pCurrentHotkey(currentHotkey)
  , pRed{ red }
  , pGreen{ green }
  , pYellow{ yellow }
  , pBackground(background)
  , mPlayerStats(stats),
  mInventoryDefaultPosition{ // Equipment
                        SDL_FPoint{ 20, 20 },
                        SDL_FPoint{ 40, 20 },
                        SDL_FPoint{ 20, 40 },
                        SDL_FPoint{ 40, 40 },
                        SDL_FPoint{ 60, 40 },
                        SDL_FPoint{ 40, 60 },
                        //Bags
                        SDL_FPoint{ 100, 20 },
                        SDL_FPoint{ 120, 20 },
                        SDL_FPoint{ 140, 20},
                        SDL_FPoint{ 160, 20 },
                        SDL_FPoint{ 100, 40 },
                        SDL_FPoint{ 120, 40 },
                        SDL_FPoint{ 140, 40},
                        SDL_FPoint{ 160, 40 },
                        SDL_FPoint{ 100, 60 },
                        SDL_FPoint{ 120, 60 },
                        SDL_FPoint{ 140, 60},
                        SDL_FPoint{ 160, 60 },
                        SDL_FPoint{ 100, 80 },
                        SDL_FPoint{ 120, 80 },
                        SDL_FPoint{ 140, 80},
                        SDL_FPoint{ 160, 80 },
                        //Spells
                        SDL_FPoint {20,120},
                        SDL_FPoint {40,120},
                        SDL_FPoint {60,120},
                        SDL_FPoint {80,120},
                        SDL_FPoint {100,120},
                        SDL_FPoint {120,120},
                        SDL_FPoint {140,120},
                        SDL_FPoint {160,120}
  }
  , mIndicatorsDrawData{ { pCurrentHotkey->getTexture(), nullptr, new SDL_FRect{} },
                        { pBackground->getTexture(), nullptr, new SDL_FRect{} },
                        { pBackground->getTexture(), nullptr, new SDL_FRect{} },
                        { pBackground->getTexture(), nullptr, new SDL_FRect{} },

                        { pRed->getTexture(), pRed->getAnimatedViewport(), new SDL_FRect{} },
                        { pGreen->getTexture(), pGreen->getAnimatedViewport(), new SDL_FRect{} },
                        { pYellow->getTexture(), pYellow->getAnimatedViewport(), new SDL_FRect{} } } {
    updateInventory();

    updateIndicators();
}

UserInterface::~UserInterface() {
    // Cleaning
    for (auto data : mIndicatorsDrawData) {
        delete data.Position;
    }
}

Graphics::Texture*&
UserInterface::getIcon() {
    return pIconTexture;
}

std::pair<float, float>
UserInterface::calculateCenter() const {
    const auto x = (mScale.windowWidthF / mScale.selectedScale) / 2.0f;
    const auto y = (mScale.windowHeightF / mScale.selectedScale) / 2.0f;
    return { x, y };
}

float
UserInterface::calculateLength(const int& points) {
    const auto value = std::min(points, 50);
    return static_cast<float>(Utility::Scale(value, 0, 50, 50, 130));
}

}