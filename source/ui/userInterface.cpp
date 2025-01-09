#include <graphics/graphics.hpp>
#include <ui/userInterface.hpp>
#include <utility/scale.hpp>
namespace Engine::UI {

UserInterface::UserInterface(std::shared_ptr<Graphics::Graphics> graphics,
                             SDL_Renderer*& renderer,
                             Common::typeScale& scale,
                             //Related to inventory
                             std::array<Items::Slot, 30>& slots,
                             Stats::Stats&                   stats)
  : pRenderer(renderer)
  ,mScale(scale)
  ,mGraphics(graphics)
  //Inventory
  ,pInventoryBackground(GET_USERINTERFACE("Inventory"))
  ,pInventorySelector(GET_USERINTERFACE("Selector"))
  , mInventorySlots(slots)
  ,mInventorySelectorVisible(false)
  ,mInventoryBackgroundDrawData(pInventoryBackground->getTexture(), nullptr, new SDL_FRect(0.0f, 0.0f, 0.0f, 0.0f))
  ,mInventorySelectorDrawData(pInventorySelector->getTexture(), nullptr)
  //Indicators
  , pIndicatorBackground(GET_USERINTERFACE("CurrentHotkey"))
  , pIndicatorRed{ GET_ANIMATED("GradientRed") }
  , pIndicatorGreen{ GET_ANIMATED("GradientGreen") }
  , pIndicatorYellow{ GET_ANIMATED("GradientYellow")}
  , pIndicatorBarBackground(GET_GENERATED("282828"))
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
  , mIndicatorsDrawData{ { pIndicatorBackground->getTexture(), nullptr, new SDL_FRect{} },
                        { pIndicatorBarBackground->getTexture(), nullptr, new SDL_FRect{} },
                        { pIndicatorBarBackground->getTexture(), nullptr, new SDL_FRect{} },
                        { pIndicatorBarBackground->getTexture(), nullptr, new SDL_FRect{} },

                        { pIndicatorRed->getTexture(), pIndicatorRed->getAnimatedViewport(), new SDL_FRect{} },
                        { pIndicatorGreen->getTexture(), pIndicatorGreen->getAnimatedViewport(), new SDL_FRect{} },
                        { pIndicatorYellow->getTexture(), pIndicatorYellow->getAnimatedViewport(), new SDL_FRect{} } } {
    updateInventory();
    updateIndicators();
    updateStats();
}

UserInterface::~UserInterface() {
    // Cleaning
    for (auto data : mIndicatorsDrawData) {
        delete data.Position;
    }
    delete mInventoryBackgroundDrawData.Position;
}

Graphics::Texture*&
UserInterface::getIcon() {
    return pIndicatorIcon;
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