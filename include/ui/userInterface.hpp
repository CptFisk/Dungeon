#pragma once
#include <array>
#include <common/scale.hpp>
#include <graphics/types/animatedTexture.hpp>
#include <graphics/types/drawData.hpp>
#include <graphics/types/generatedTexture.hpp>
#include <graphics/types/userInterfaceTexture.hpp>
#include <graphicsForward.hpp>
#include <items/slot.hpp>
#include <stats/stats.hpp>
#include <vector>

namespace Engine::UI {
/**
 * @brief Handle all the visible elements of the userinterface
 * @details Handle the display of current selected item, health, stamina and luck-bar.
 */
class UserInterface {
  public:
    UserInterface(std::shared_ptr<Graphics::Graphics> graphics,
                  SDL_Renderer*&                      renderer,
                  Common::typeScale&                  scale,
                  // Related to inventory
                  std::array<Items::Slot, 30>& slots,
                  Stats::Stats&                stats);
    ~UserInterface();

    [[nodiscard]] std::vector<Graphics::typeDrawData> getIndicators() const;
    [[nodiscard]] std::vector<Graphics::typeDrawData> getInventory();
    /**
     *@brief Calculate new positions for all graphical elements based on resolution
     */
    void updateIndicators();
    void updateInventory();
    void updateStats();
    /**
     * @brief Calculate values for gradients
     */
    void updateBars();
    /**
     * @return Returns a reference the to icon so the inventory can change it
     */
    Graphics::Texture*& getIcon();
    /**
     * @brief Select a item in the inventory with the mouse
     * @param point Position of the mouse on the screen
     * @retrun The index that the user clicked on. If user clicked out of screen no index is returned
     */
    [[nodiscard]] std::optional<uint8_t> selectItemMouse(const SDL_FPoint& point);
    /**
     * @return Return a reference to @ref mSelectorVisible, this is used in items/inventory.cpp
     */
    [[nodiscard]] bool& getSelectorVisible();

  protected:
    /**
     * @brief Calculate the length for a given bar, based on the max points
     * @param points Number of points spend on that attribute
     * @return Value to be used as width for graphic
     */
    [[nodiscard]] static float            calculateLength(const int& points);
    [[nodiscard]] std::pair<float, float> calculateCenter() const;

  private:
    // Global variables
    Stats::Stats&      mPlayerStats; // Reference to the player stats
    Common::typeScale& mScale;       // Current resolution scale
    SDL_Renderer*      pRenderer;    // Reference to the renderer, used when generating the new background
    /**
     * @brief Reference to the graphics handler, this is to avoid massive parameters on the constructors
     */
    std::shared_ptr<Graphics::Graphics> mGraphics;

#pragma region Indicators
    Graphics::UserInterfaceTexture*           pIndicatorBackground;
    Graphics::Texture*                        pIndicatorIcon;
    Graphics::AnimatedTexture*                pIndicatorRed;    // Health
    Graphics::AnimatedTexture*                pIndicatorGreen;  // Stamina
    Graphics::AnimatedTexture*                pIndicatorYellow; // Luck meter
    Graphics::GeneratedTexture*               pIndicatorBarBackground;
    const std::vector<Graphics::typeDrawData> mIndicatorsDrawData;
#pragma endregion
#pragma region Inventory
    // Graphical items
    Graphics::UserInterfaceTexture* pInventoryBackground;
    Graphics::UserInterfaceTexture* pInventorySelector;
    // Draw data
    Graphics::typeDrawData mInventoryBackgroundDrawData;
    Graphics::typeDrawData mInventorySelectorDrawData;
    // Positions
    const std::array<SDL_FPoint, 30> mInventoryDefaultPosition; // Base offsets of all positions
    std::array<SDL_FRect, 30>        mInventoryPositions;       // Positions based on resolution

    std::array<Items::Slot, 30>& mInventorySlots; // Reference to the items
    bool                         mInventorySelectorVisible;
#pragma endregion
#pragma region Stats

#pragma endregion
};

}