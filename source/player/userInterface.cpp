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
  , mRed{ red }
  , mGreen{ green }
  , mYellow{ yellow }
  , pBackground(background)
  , mHotkeyPosition{}
  , mPlayerStats(stats)
  , mDrawData{ { pCurrentHotkey->getTexture(), nullptr, &mHotkeyPosition },
               { pBackground->getTexture(), nullptr, &mRed.mBackgroundPosition },
               { pBackground->getTexture(), nullptr, &mGreen.mBackgroundPosition },
               { pBackground->getTexture(), nullptr, &mYellow.mBackgroundPosition },

               { mRed.pTexture->getTexture(), mRed.pTexture->getAnimatedViewport(), &mRed.mBarPosition },
               { mGreen.pTexture->getTexture(), mGreen.pTexture->getAnimatedViewport(), &mGreen.mBarPosition },
               { mYellow.pTexture->getTexture(), mYellow.pTexture->getAnimatedViewport(), &mYellow.mBarPosition } } {
    updateInterface();
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
    mHotkeyPosition.x = pCurrentHotkey->getMarginLeftF();
    mHotkeyPosition.y = pCurrentHotkey->getMarginTopF();
    mHotkeyPosition.w = pCurrentHotkey->getWidthF();
    mHotkeyPosition.h = pCurrentHotkey->getHeightF();

    // Red bar background
    mRed.mBackgroundPosition.x = mHotkeyPosition.x + mHotkeyPosition.w + 4;
    mRed.mBackgroundPosition.y = mHotkeyPosition.y + 1.0f;
    mRed.mBackgroundPosition.w = calculateLength(mPlayerStats.Vitality);
    mRed.mBackgroundPosition.h = 4.0f;

    // Green bar background
    mGreen.mBackgroundPosition.x = mRed.mBackgroundPosition.x;
    mGreen.mBackgroundPosition.y = mRed.mBackgroundPosition.y + 5.0f;
    mGreen.mBackgroundPosition.w = calculateLength(mPlayerStats.Stamina);
    mGreen.mBackgroundPosition.h = 4.0f;

    // Yellow bar background
    mYellow.mBackgroundPosition.x = mGreen.mBackgroundPosition.x;
    mYellow.mBackgroundPosition.y = mGreen.mBackgroundPosition.y + 5.0f;
    mYellow.mBackgroundPosition.w = 52.0f;
    mYellow.mBackgroundPosition.h = 4.0f;

    // Red bar
    mRed.mBarPosition.x = mRed.mBackgroundPosition.x + 1.0f;
    mRed.mBarPosition.y = mRed.mBackgroundPosition.y + 1.0f;
    mRed.mBarPosition.w = 10.0f;
    mRed.mBarPosition.h = 2.0f;

    // Green bar
    mGreen.mBarPosition.x = mGreen.mBackgroundPosition.x + 1.0f;
    mGreen.mBarPosition.y = mGreen.mBackgroundPosition.y + 1.0f;
    mGreen.mBarPosition.w = 10.0f;
    mGreen.mBarPosition.h = 2.0f;

    // Yellow bar
    mYellow.mBarPosition.x = mYellow.mBackgroundPosition.x + 1.0f;
    mYellow.mBarPosition.y = mYellow.mBackgroundPosition.y + 1.0f;
    mYellow.mBarPosition.w = 50.0f;
    mYellow.mBarPosition.h = 2.0f;
}

void
UserInterface::updateBars() {}

}