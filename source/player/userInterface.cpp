#include <player/userInterface.hpp>

namespace Player {
UserInterface::UserInterface(Graphics::UserInterfaceTexture* currentHotkey,
                             Graphics::AnimatedTexture*      red,
                             Graphics::AnimatedTexture*      green,
                             Graphics::AnimatedTexture*      yellow,
                             Graphics::GeneratedTexture*     background)
  : pCurrentHotkey(currentHotkey)
  , mRed{ red }
  , mGreen{ green }
  , mYellow{ yellow }
  , pBackground(background)
  , mHotkeyPosition{}
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

void
UserInterface::updateInterface() {
    mHotkeyPosition.x = pCurrentHotkey->getMarginLeftF();
    mHotkeyPosition.y = pCurrentHotkey->getMarginTopF();
    mHotkeyPosition.w = pCurrentHotkey->getWidthF();
    mHotkeyPosition.h = pCurrentHotkey->getHeightF();
    //Use same positions as icon
    mIconPosition = mHotkeyPosition;

    // Red bar
    mRed.mBarPosition.x = mHotkeyPosition.x + mHotkeyPosition.w + 5.0f;
    mRed.mBarPosition.y = mHotkeyPosition.y + 2.0f;
    mRed.mBarPosition.w = 100.0f;
    mRed.mBarPosition.h = 2.0f;

    // Red bar background
    mRed.mBackgroundPosition.x = mRed.mBarPosition.x - 1.0f;
    mRed.mBackgroundPosition.y = mRed.mBarPosition.y - 1.0f;
    mRed.mBackgroundPosition.w = mRed.mBarPosition.w + 2.0f;
    mRed.mBackgroundPosition.h = mRed.mBarPosition.h + 2.0f;

    // Green bar
    mGreen.mBarPosition.x = mRed.mBarPosition.x;
    mGreen.mBarPosition.y = mRed.mBarPosition.y + 5.0f;
    mGreen.mBarPosition.w = 100.0f;
    mGreen.mBarPosition.h = 2.0f;

    // Green bar background
    mGreen.mBackgroundPosition.x = mGreen.mBarPosition.x - 1.0f;
    mGreen.mBackgroundPosition.y = mGreen.mBarPosition.y - 1.0f;
    mGreen.mBackgroundPosition.w = mGreen.mBarPosition.w + 2.0f;
    mGreen.mBackgroundPosition.h = mGreen.mBarPosition.h + 2.0f;

    // Yellow bar
    mYellow.mBarPosition.x = mGreen.mBarPosition.x;
    mYellow.mBarPosition.y = mGreen.mBarPosition.y + 5.0f;
    mYellow.mBarPosition.w = 50.0f;
    mYellow.mBarPosition.h = 2.0f;

    // Yellow bar background
    mYellow.mBackgroundPosition.x = mYellow.mBarPosition.x - 1.0f;
    mYellow.mBackgroundPosition.y = mYellow.mBarPosition.y - 1.0f;
    mYellow.mBackgroundPosition.w = mYellow.mBarPosition.w + 2.0f;
    mYellow.mBackgroundPosition.h = mYellow.mBarPosition.h + 2.0f;
}

void
UserInterface::updateBars() {}

}