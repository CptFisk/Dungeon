#include <ui/userInterface.hpp>
#include <utility/scale.hpp>

namespace Engine::UI {

UserInterface::UserInterface(Common::typeScale&              scale,
                             Graphics::UserInterfaceTexture* currentHotkey,
                             Graphics::AnimatedTexture*      red,
                             Graphics::AnimatedTexture*      green,
                             Graphics::AnimatedTexture*      yellow,
                             Graphics::GeneratedTexture*     background,
                             Stats::Stats&                   stats)
  : mScale(scale)
  , pCurrentHotkey(currentHotkey)
  , pRed{ red }
  , pGreen{ green }
  , pYellow{ yellow }
  , pBackground(background)
  , mPlayerStats(stats)
  , mIndicatorsDrawData{ { pCurrentHotkey->getTexture(), nullptr, new SDL_FRect{} },
                        { pBackground->getTexture(), nullptr, new SDL_FRect{} },
                        { pBackground->getTexture(), nullptr, new SDL_FRect{} },
                        { pBackground->getTexture(), nullptr, new SDL_FRect{} },

                        { pRed->getTexture(), pRed->getAnimatedViewport(), new SDL_FRect{} },
                        { pGreen->getTexture(), pGreen->getAnimatedViewport(), new SDL_FRect{} },
                        { pYellow->getTexture(), pYellow->getAnimatedViewport(), new SDL_FRect{} } } {
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

std::pair<int, int>
UserInterface::calculateCenter() {
    const auto x = static_cast<int>((mScale.windowWidthF / mScale.selectedScale) / 2.0f);
    const auto y = static_cast<int>((mScale.windowHeightF / mScale.selectedScale) / 2.0f);
    return { x, y };
}

float
UserInterface::calculateLength(const int& points) {
    const auto value = std::min(points, 50);
    return static_cast<float>(Utility::Scale(value, 0, 50, 50, 130));
}



}