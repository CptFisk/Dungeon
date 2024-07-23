#include <algorithm>
#include <editor/tile.hpp>
#include <global.hpp>
#include <graphics/animatedTexture.hpp>
#include <graphics/graphics.hpp>
#include <iostream>
#include <utility/vector.hpp>

namespace Editor {

Tile::Tile(const int& x, const int& y, const Common::typeScale& scale, Graphics::typeSimpleTexture& number, SDL_Renderer* renderer)
  : pRenderer(renderer)
  , xPos(static_cast<float>(x) * 16.0f * scale.factorX)
  , yPos(static_cast<float>(y) * 16.0f * scale.factorY)
  , scale(scale)
  , numbers(number)
  , tileData{}
  , standardPosition(xPos, yPos, 16.0f * scale.factorX, 16.0f * scale.factorY)
  , mOverlay{} {

    // Setup overlay
    mOverlay.Texture = SDL_CreateTexture(
      renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, INT(16.0f * scale.factorX), INT(16.0f * scale.factorY));
    if (mOverlay.Texture == nullptr)
        std::cout << "Error in creating texture" << std::endl;
    mOverlay.Position = &standardPosition;
    mOverlay.Viewport = nullptr;
    SDL_SetTextureBlendMode(mOverlay.Texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(mOverlay.Texture, 127);
}

Tile::~Tile() {
    clear();
    SDL_DestroyTexture(mOverlay.Texture); // Cleanup
}

void
Tile::clear() {
    for (auto& element : baseLayer) {
        delete element.Position;
    }
    for (auto& element : topLayer) {
        delete element.Position;
    }
    baseLayer.clear();
    topLayer.clear();
    tileData = {};
}

int
Tile::addData(const std::string&                         asset,
              Level::typeAssets&                   assetList,
              const std::shared_ptr<Graphics::Graphics>& graphics,
              const bool&                                mode) {
    return addData(asset, assetList, graphics, mode ? Mouse::TOP_LAYER : Mouse::TEXTURE);
}

int
Tile::addData(const std::string&                         asset,
              Level::typeAssets&                   assetList,
              const std::shared_ptr<Graphics::Graphics>& graphics,
              const Mouse&                               mouse) {
    auto&      data           = mouse == Mouse::TEXTURE ? baseLayer : topLayer;
    auto       tileType       = mouse == Mouse::TEXTURE ? Level::TileType::BASE_TEXTURE : Level::TileType::TOP_TEXTURE;
    const auto type           = graphics->getTextureType(asset);
    int        animationValue = 0;
    switch (type) {
        case Graphics::TextureTypes::BaseTexture:
            if (graphics->getTexture<Graphics::typeSimpleTexture>(asset) != nullptr) {
                // The asset exist and we can use it
                data.emplace_back(graphics->getTexture<Graphics::typeSimpleTexture>(asset)->getTexture(),
                                  &graphics->getTexture<Graphics::typeSimpleTexture>(asset)->getRandomView(),
                                  new SDL_FRect{
                                    xPos,
                                    yPos,
                                    FLOAT(graphics->getTexture<Graphics::typeSimpleTexture>(asset)->Width) * scale.factorX,
                                    FLOAT(graphics->getTexture<Graphics::typeSimpleTexture>(asset)->Height) * scale.factorY,
                                  });
            }
            break;
        case Graphics::TextureTypes::AnimatedTexture:
            if (graphics->getTexture<Graphics::AnimatedTexture*>(asset) != nullptr) {
                // The asset exist and we can use it
                data.emplace_back((*graphics->getTexture<Graphics::AnimatedTexture*>(asset))->getTexture(),
                                  (*graphics->getTexture<Graphics::AnimatedTexture*>(asset))->getViewport(),
                                  new SDL_FRect{
                                    xPos,
                                    yPos,
                                    FLOAT((*graphics->getTexture<Graphics::AnimatedTexture*>(asset))->Width) * scale.factorX,
                                    FLOAT((*graphics->getTexture<Graphics::AnimatedTexture*>(asset))->Height) * scale.factorY,
                                  });
                animationValue = INT((*graphics->getTexture<Graphics::AnimatedTexture*>(asset))->getViewports().size() *
                                     (*graphics->getTexture<Graphics::AnimatedTexture*>(asset))->getTicks());
            }
            break;
        default:;
    }
    // Handles the list of assets
    if (Level::findAsset(asset, assetList).has_value()) {
        // The item exist in asset list. Append it to the end of our graphics
        switch (mouse) {
            case Mouse::TEXTURE:
                tileData.Base.emplace_back(Level::findAsset(asset, assetList).value());
                break;
            case Mouse::TOP_LAYER:
                tileData.Top.emplace_back(Level::findAsset(asset, assetList).value());
                break;
            default:;
        }
    } else {
        switch (mouse) {
            case Mouse::TEXTURE:
                tileData.Base.emplace_back(Level::addAsset(asset, assetList));
                break;
            case Mouse::TOP_LAYER:
                tileData.Top.emplace_back(Level::addAsset(asset, assetList));
                break;
            default:;
        }
    }
    tileData.Type.set(tileType);
    return animationValue;
}

void
Tile::addOverlay(SDL_Texture* overlay) {
    SDL_FRect destination;
    if (overlays.empty()) {
        SDL_SetRenderTarget(pRenderer, mOverlay.Texture);
        SDL_RenderCopyF(pRenderer, overlay, nullptr, nullptr);
        SDL_SetRenderTarget(pRenderer, nullptr);
    } else {
        switch (overlays.size()) {
            case 1:
                SDL_SetRenderTarget(pRenderer, mOverlay.Texture);
                destination = SDL_FRect{ 0.0f, 8.0f * scale.factorY, 16.0f * scale.factorX, 8.0f * scale.factorY };
                SDL_RenderCopyF(pRenderer, overlay, nullptr, &destination);
                SDL_SetRenderTarget(pRenderer, nullptr);
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
        }
    }
    overlays.insert(overlay);
}

void
Tile::addType(const Level::TileType& value, SDL_Texture* overlay) {
    tileData.Type.set(value);
    if (overlays.find(overlay) == overlays.end())
        addOverlay(overlay);
}

void
Tile::addLightning(const Editor::LightningShape& shape, const Editor::LightningColour& colour, const Editor::LightningSize& size) {
    /*
    Since the enums for shape, colour and size have the same values as the one in Level::Types they can be cast directly
        between each other.
    */
    tileData.Type.set(shape);
    tileData.Type.set(colour);
    tileData.Type.set(size);
}

std::vector<Common::typeDrawData>
Tile::getBaseDrawData() {
    return baseLayer;
}

std::vector<Common::typeDrawData>
Tile::getTopDrawData() {
    return topLayer;
}

Common::typeDrawData
Tile::getNumbers() {
    return { numbers.getTexture(), &numbers.getView(baseLayer.size()), &standardPosition };
}

Common::typeDrawData
Tile::getOverlay() {
    return mOverlay;
}

bool
Tile::elementExist(SDL_Texture* texture, const uint8_t& id) const {
    auto t1 = std::find_if(baseLayer.begin(), baseLayer.end(), [&texture](const Common::typeDrawData& d) { return d.Texture == texture; });
    auto t2 = std::find_if(topLayer.begin(), topLayer.end(), [&texture](const Common::typeDrawData& d) { return d.Texture == texture; });
    auto i1 = std::find_if(tileData.Base.begin(), tileData.Base.end(), [&id](const uint8_t& d) { return d == id; });
    auto i2 = std::find_if(tileData.Top.begin(), tileData.Top.end(), [&id](const uint8_t& d) { return d == id; });
    return t1 != baseLayer.end() || t2 != topLayer.end() || i1 != tileData.Base.end() || i2 != tileData.Top.end() ? true : false;
}

void
Tile::removeElement(SDL_Texture* texture, const uint8_t& id) {
    // Remove from all the vectors
    Utility::removeElementInVector(baseLayer, [texture](const Common::typeDrawData a) { return a.Texture == texture; });
    Utility::removeElementInVector(topLayer, [texture](const Common::typeDrawData a) { return a.Texture == texture; });
    Utility::removeElementInVector(tileData.Base, [id](const uint8_t& a) { return a == id; });
    Utility::removeElementInVector(tileData.Top, [id](const uint8_t& a) { return a == id; });
    // Now lower all the values that was above the  id for base and top
    for (auto& element : tileData.Base) {
        if (element > id)
            --element;
    }
    for (auto& element : tileData.Top) {
        if (element > id)
            --element;
    }
}

Level::typeTileData
Tile::getTileData() const {
    return tileData;
}

}