#pragma once
#include <graphics/types/animatedTexture.hpp>
#include <graphics/types/drawData.hpp>
#include <graphics/types/generatedTexture.hpp>
#include <graphics/types/userInterfaceTexture.hpp>
#include <stats/stats.hpp>
#include <vector>

namespace Player {
/**
 * @brief Handle all the visible elements of the userinterface
 * @details Handle the display of current selected item, health, stamina and luck-bar.
 */
class UserInterface {
  public:
    UserInterface(Graphics::UserInterfaceTexture* currentHotkey,
                  Graphics::AnimatedTexture*      red,
                  Graphics::AnimatedTexture*      green,
                  Graphics::AnimatedTexture*      yellow,
                  Graphics::GeneratedTexture*     background,
                  Stats::Stats&                   stats);
    ~UserInterface();

    [[nodiscard]] std::vector<Graphics::typeDrawData> getUserInterface() const;
    // Calculate new positions
    void updateInterface();
    /**
     * @brief Calculate values for gradients
     */
    void updateBars();
    /**
     * @return Returns a reference the to icon so the inventory can change it
     */
    Graphics::Texture*& getIcon();

  protected:
    /**
     * @brief Calculate the length for a given bar, based on the max points
     * @param points Number of points spend on that attribute
     * @return Value to be used as width for graphic
     */
    [[nodiscard]] static float calculateLength(const int& points);

  private:
    Stats::Stats&                   mPlayerStats; // Reference to the player stats
    Graphics::UserInterfaceTexture* pCurrentHotkey;
    Graphics::Texture*              pIconTexture;
    Graphics::AnimatedTexture*      pRed;    // Health
    Graphics::AnimatedTexture*      pGreen;  // Stamina
    Graphics::AnimatedTexture*      pYellow; // Luck meter

    Graphics::GeneratedTexture* pBackground;

    const std::vector<Graphics::typeDrawData> mDrawData;
};

}