#include <player/userInterface.hpp>
#include <utility/scale.hpp>
namespace Player {
UserInterface::UserInterface(Graphics::UserInterfaceTexture* currentHotkey,
                             Graphics::AnimatedTexture*      red,
                             Graphics::AnimatedTexture*      green,
                             Graphics::AnimatedTexture*      yellow,
                             Graphics::GeneratedTexture*     background,
                             Stats::Stats&                   stats)
  : pCurrentHotkey(currentHotkey)
  , pRed{ red }
  , pGreen{ green }
  , pYellow{ yellow }
  , pBackground(background)
  , mPlayerStats(stats)
  , mDrawData{ { pCurrentHotkey->getTexture(), nullptr, new SDL_FRect{} },
               { pBackground->getTexture(), nullptr, new SDL_FRect{} },
               { pBackground->getTexture(), nullptr, new SDL_FRect{} },
               { pBackground->getTexture(), nullptr, new SDL_FRect{} },

               { pRed->getTexture(), pRed->getAnimatedViewport(), new SDL_FRect{} },
               { pGreen->getTexture(), pGreen->getAnimatedViewport(), new SDL_FRect{} },
               { pYellow->getTexture(), pYellow->getAnimatedViewport(), new SDL_FRect{} } } {
    updateInterface();
}

UserInterface::~UserInterface() {
    // Cleaning
    for (auto data : mDrawData) {
        delete data.Position;
    }
}

std::vector<Graphics::typeDrawData>
UserInterface::getUserInterface() const {
    return mDrawData;
}

Graphics::Texture*&
UserInterface::getIcon() {
    return pIconTexture;
}

float
UserInterface::calculateLength(const int& points) {
    const auto value = std::min(points, 50);
    return static_cast<float>(Utility::Scale(value, 0, 50, 50, 130));
}

void
UserInterface::updateInterface() {
    auto& hotkeyPosition = mDrawData.front().Position;
    hotkeyPosition->x    = pCurrentHotkey->getMarginLeftF();
    hotkeyPosition->y    = pCurrentHotkey->getMarginTopF();
    hotkeyPosition->w    = pCurrentHotkey->getWidthF();
    hotkeyPosition->h    = pCurrentHotkey->getHeightF();

    // Red bar background
    auto& redBg = mDrawData.at(1).Position;
    redBg->x    = hotkeyPosition->x + hotkeyPosition->w + 4;
    redBg->y    = hotkeyPosition->y + 1.0f;
    redBg->w    = calculateLength(mPlayerStats.Vitality);
    redBg->h    = 4.0f;

    // Green bar background
    auto& greenBg = mDrawData.at(2).Position;
    greenBg->x    = redBg->x;
    greenBg->y    = redBg->y + 5.0f;
    greenBg->w    = calculateLength(mPlayerStats.Stamina);
    greenBg->h    = 4.0f;

    // Yellow bar background
    auto& yellowBg = mDrawData.at(3).Position;
    yellowBg->x    = greenBg->x;
    yellowBg->y    = greenBg->y + 5.0f;
    yellowBg->w    = 52.0f;
    yellowBg->h    = 4.0f;

    // Red bar
    auto& redBar = mDrawData.at(4).Position;
    redBar->x    = redBg->x + 1.0f;
    redBar->y    = redBg->y + 1.0f;
    redBar->w    = 10.0f;
    redBar->h    = 2.0f;

    // Green bar
    auto& greenBar = mDrawData.at(4).Position;
    greenBar->x    = greenBg->x + 1.0f;
    greenBar->y    = greenBg->y + 1.0f;
    greenBar->w    = 10.0f;
    greenBar->h    = 2.0f;

    // Yellow bar
    auto& yellowBar = mDrawData.at(5).Position;
    yellowBar->x    = yellowBg->x + 1.0f;
    yellowBar->y    = yellowBg->y + 1.0f;
    yellowBar->w    = 50.0f;
    yellowBar->h    = 2.0f;
}

void
UserInterface::updateBars() {}

}