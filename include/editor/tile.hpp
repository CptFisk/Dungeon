#pragma once
#include <SDL.h>
#include <cmake.hpp>
#include <common/scale.hpp>
#include <common/structures.hpp>
#include <editor/utility/mouse.hpp>
#include <editor/utility/mouseLightning.hpp>
#include <graphics/structures.hpp>
#include <graphics/types/simpleTexture.hpp>
#include <graphicsForward.hpp>
#include <level/types/assets.hpp>
#include <level/types/tile.hpp>
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
    Tile(const int&                   x,
         const int&                   y,
         const Common::typeScale&     scale,
         Graphics::typeSimpleTexture& number,
         SDL_Renderer*                renderer); // Used in editor mode
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
                Level::typeAssets&                         assetList,
                const std::shared_ptr<Graphics::Graphics>& graphics,
                const bool&                                mode);
    int addData(const std::string&                         asset,
                Level::typeAssets&                         assetList,
                const std::shared_ptr<Graphics::Graphics>& graphics,
                const Mouse&                               mouse);
    /**
     * @brief Clear the last data that was added
     */
    void clearLastData();
    void addMonster(const int& id, SDL_Texture* texture, const SDL_Rect& viewport);
    /**
     * @brief Add a new value to the tile type
     * @param value
     */
    void addType(const Level::TileType& value, SDL_Texture* overlay);
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
    [[nodiscard]] std::vector<Common::typeDrawData> getBaseDrawData();
    [[nodiscard]] std::vector<Common::typeDrawData> getTopDrawData();

    [[nodiscard]] Common::typeDrawData getNumbers(); // Return a graphic that display the number of graphics used
    [[nodiscard]] Common::typeDrawData getOverlay();

    [[nodiscard]] bool elementExist(SDL_Texture* texture, const uint8_t& id) const;
    void               removeElement(SDL_Texture* texture, const uint8_t& id);

    [[nodiscard]] Level::typeTileData getTileData() const;

    void addOverlay(SDL_Texture* overlay);

  private:
    void generateOverlay();

  protected:
    SDL_Renderer*           pRenderer;        // Used for generating overlays
    const float             xPos;             // Position in map
    const float             yPos;             // Position in map
    SDL_FRect               standardPosition; // Position on the map
    const Common::typeScale scale;            // Scale of resolution

    Level::typeTileData tileData; // Tile data

    std::set<SDL_Texture*>            overlays; // All overlays
    Graphics::typeSimpleTexture&      numbers;  // Graphics to hold numbers
    std::vector<Common::typeDrawData> baseLayer;
    std::vector<Common::typeDrawData> topLayer;
    bool                              lastLayer; // False = baseLayer, True = topLayer
    Common::typeDrawData              mOverlay;  // Overlay
};
}