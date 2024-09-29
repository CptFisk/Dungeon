#pragma once
#include <SDL.h>
#include <cmake.hpp>
#include <common/scale.hpp>
#include <common/tile.hpp>
#include <editor/utility/mouse.hpp>
#include <editor/utility/mouseLightning.hpp>
#include <file/types/editorAssets.hpp>
#include <file/types/editorTile.hpp>
#include <graphics/types/drawData.hpp>
#include <graphics/types/font.hpp>
#include <graphics/types/generatedTexture.hpp>
#include <graphicsForward.hpp>
#include <memory>
#include <set>
#include <variant>
#include <vector>

namespace Editor {
/**
 * @brief Internal structure for the visibility of a tile
 */
struct tileData {
    SDL_Texture* Texture;
    SDL_Rect*    Viewport;
    SDL_FRect    Position;
};

/**
 * @brief Basic class to hold all the data related to a tile. It will hold position and all the different textures.
 */
class Tile {
  public:
    Tile(const int& x, const int& y, const Common::typeScale& scale, Graphics::Font* font, SDL_Renderer* renderer);
    ~Tile();

    [[maybe_unused]] void clear(); // Clear vector

    /**
     * @brief Used to add a graphic to a tile. The function handle the types internally (both animated and base-textures). It also
     * @brief add it to the base or top-layer list
     * @param asset Name of the asset
     * @param assetList Reference to asset list
     * @param graphics Reference to graphic engine
     * @param mode True if top-layer, otherwise false
     * @return Value of animation value, if static texture returns 0
     */
    int addData(const std::string&                         asset,
                File::typeAssets&                          assetList,
                const std::shared_ptr<Graphics::Graphics>& graphics,
                const bool&                                mode);
    int addData(const std::string&                         asset,
                File::typeAssets&                          assetList,
                const std::shared_ptr<Graphics::Graphics>& graphics,
                const Mouse&                               mouse);
    /**
     * @brief Clear the last data that was added
     */
    void clearLastData();
    void addUnit(const int& id, SDL_Texture* texture, const SDL_Rect& viewport, const int& start, const int& stop);
    /**
     * @brief Add a new value to the tile type
     * @param value
     */
    void addType(const Common::TileType& value, Graphics::GeneratedTexture* overlay);
    /**
     * @brief Clear all types from a tile
     */
    void clearType();
    /**
     * @brief Add a lightning effect to the tile.
     * @param shape Shape of tile, either square or circle
     * @param colour Colour of the effect
     * @param size Size of the effect
     */
    void addLightning(const LightningShape& shape, const LightningColour& colour, const LightningSize& size);
    [[nodiscard]] std::vector<Graphics::typeDrawData> getBaseDrawData();
    [[nodiscard]] std::vector<Graphics::typeDrawData> getTopDrawData();

    [[nodiscard]] Graphics::typeDrawData getNumbers(); // Return a graphic that display the number of graphics used
    [[nodiscard]] Graphics::typeDrawData getOverlay();

    [[nodiscard]] bool elementExist(SDL_Texture* texture, const uint8_t& id) const;
    void               removeElement(SDL_Texture* texture, const uint8_t& id);

    [[nodiscard]] File::typeTileData getTileData() const;

    void addOverlay(Graphics::GeneratedTexture* overlay);

  private:
    void generateOverlay();

  protected:
    SDL_Renderer*            pRenderer;         // Used for generating overlays
    const float              mPosX;             // Position in map
    const float              mPosY;             // Position in map
    SDL_FRect                mStandardPosition; // Position on the map
    const Common::typeScale& mScale;            // Scale of resolution

    File::typeTileData mTileData; // Tile data

    std::set<SDL_Texture*>              mOverlays; // All overlays
    Graphics::Font*                     pFont;     // Graphics to fonts
    std::vector<Graphics::typeDrawData> mBaseLayer;
    std::vector<Graphics::typeDrawData> mTopLayer;
    bool                                mLastLayer; // False = baseLayer, True = topLayer
    Graphics::typeDrawData              mOverlay;   // Overlay
};
}