#include <algorithm>
#include <editor/tile.hpp>
#include <global.hpp>
#include <graphics/animatedTexture.hpp>
#include <graphics/graphics.hpp>
#include <iostream>
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

bool
Tile::addData(const std::string& asset, Level::File::typeAssets& assetList, const std::shared_ptr<Graphics::Graphics>& graphics, const bool& mode) {
    return addData(asset, assetList, graphics, mode ? Mouse::TOP_LAYER : Mouse::TEXTURE);
}

bool
Tile::addData(const std::string& asset, Level::File::typeAssets& assetList, const std::shared_ptr<Graphics::Graphics>& graphics,  const Mouse& mouse) {
    auto& data = mouse == Mouse::TEXTURE ? baseLayer : topLayer;
    const auto size = data.size();
    const auto type = graphics->getTextureType(asset);
    switch (type) {
        case Graphics::TextureTypes::SIMPLE_TEXTURE:
            if (graphics->getTexture<Graphics::typeSimpleTexture>(asset) == nullptr)
                return false;
            // The asset exist and we can use it
            data.emplace_back(graphics->getTexture<Graphics::typeSimpleTexture>(asset)->getTexture(),
                              &graphics->getTexture<Graphics::typeSimpleTexture>(asset)->getRandomView(),
                              new SDL_FRect{
                                xPos,
                                yPos,
                                FLOAT(graphics->getTexture<Graphics::typeSimpleTexture>(asset)->Width) * scale.factorX,
                                FLOAT(graphics->getTexture<Graphics::typeSimpleTexture>(asset)->Height) * scale.factorY,
                              });
            tileData.Type |= static_cast<uint8_t>(Level::File::TileType::TEXTURE);
            break;
        case Graphics::TextureTypes::ANIMATED_TEXTURE:
            if (graphics->getTexture<Graphics::AnimatedTexture*>(asset) == nullptr)
                return false;
            // The asset exist and we can use it
            data.emplace_back((*graphics->getTexture<Graphics::AnimatedTexture*>(asset))->getTexture(),
                              (*graphics->getTexture<Graphics::AnimatedTexture*>(asset))->getViewport(),
                              new SDL_FRect{
                                xPos,
                                yPos,
                                FLOAT((*graphics->getTexture<Graphics::AnimatedTexture*>(asset))->Width) * scale.factorX,
                                FLOAT((*graphics->getTexture<Graphics::AnimatedTexture*>(asset))->Height) * scale.factorY,
                              });
            tileData.Type |= static_cast<uint8_t>(Level::File::TileType::ANIMATED_TEXTURE);
            break;
        default:;
    }
    // Handles the list of assets
    if (Level::File::findAsset(asset, assetList).has_value()) {
        // The item exist in asset list. Append it to the end of our graphics
        switch(mouse){
            case Mouse::TEXTURE:
                tileData.Base.emplace_back(Level::File::findAsset(asset, assetList).value());
                break;
            case Mouse::TOP_LAYER:
                tileData.Top.emplace_back(Level::File::findAsset(asset, assetList).value());
                break;
            default:
                ;
        }
    } else {
        switch(mouse){
            case Mouse::TEXTURE:
                tileData.Base.emplace_back(Level::File::addAsset(asset, assetList));
                break;
            case Mouse::TOP_LAYER:
                tileData.Top.emplace_back(Level::File::addAsset(asset, assetList));
                break;
            default:
              ;
        }
    }

    return data.size() > size ? true : false;
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
Tile::addType(const Level::File::TileType& value, SDL_Texture* overlay) {
    tileData.Type |= static_cast<uint8_t>(value);
    if (overlays.find(overlay) == overlays.end())
        addOverlay(overlay);
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
Tile::elementExist(SDL_Texture* texture) const {
    auto it = std::find_if(baseLayer.begin(), baseLayer.end(), [&texture](const Common::typeDrawData& d) { return d.Texture == texture; });
    return it != baseLayer.end() ? true : false;
}

size_t
Tile::removeElement(SDL_Texture* texture) {
    const auto size = baseLayer.size();
    for (auto it = baseLayer.begin(); it != baseLayer.end();) {
        if ((*it).Texture == texture) {
            it = baseLayer.erase(it);
        } else {
            ++it;
        }
    }
    return size - baseLayer.size();
}

Level::File::typeTileData
Tile::getTileData() const {
    return tileData;
}

}